# -*- mode: python; indent-tabs-mode: nil; tab-width: 4 -*-
# vim: set tabstop=4 shiftwidth=4 expandtab:

"""PyPlate : a simple Python-based templating program

PyPlate parses a file and replaces directives (in double square brackets [[ ... ]])
by various means using a given dictionary of variables.  Arbitrary Python code
can be run inside many of the directives, making this system highly flexible.

Usage:
# Load and parse template file
template = pyplate.Template("output") (filename or string)
# Execute it with a dictionary of variables
template.execute_file(output_stream, locals())

PyPlate defines the following directives:
   [[...]]       evaluate the arbitrary Python expression and insert the
      result into the output

   [[# ... #]]   comment.

   [[exec ...]]  execute arbitrary Python code in the sandbox namespace

   [[if ...]]    conditional expressions with usual Python semantics
   [[elif ...]]
   [[else]]
   [[end]]

   [[for ... in ...]]  for-loop with usual Python semantics
   [[end]]

   [[def ...(...)]]  define a "function" out of other templating elements
   [[end]]

   [[call ...]]  call a templating function (not a regular Python function)
 """

#
# Copyright (C) 2001-2005 Michael Droettboom
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#


import sys, string, re, gamera.util as util, io, codecs

re_directive = re.compile(r"\[\[(.*?)\]\]")
re_for_loop = re.compile(r"for (.*) in (.*)")
re_if = re.compile(r"if (.*)")
re_elif = re.compile(r"elif (.*)")
re_def = re.compile(r"def (.*?)\((.*)\)")
re_call = re.compile(r"call (.*?)\((.*)\)")
re_exec = re.compile(r"exec (.*)")
re_comment = re.compile(r"#(.*)#")

re_clean_whitespace = re.compile(r"\]\]\s+?")

############################################################
# Template parser
class ParserException(Exception):
   def __init__(self, lineno, s):
      Exception.__init__(self, "line %d: %s" % (lineno, s))

class Template:
   def __init__(self, filename=None):
      if filename is not None:
         try:
            self.parse_file(filename)
         except Exception:
            self.parse_string(filename)

   def parse_file(self, filename):
      file = open(filename, 'r')
      self.parse(file)
      file.close()

   def parse_string(self, template):
      file = io.StringIO(template)
      self.parse(file)
      file.close()

   def parse(self, file):
      self.file = file
      self.line = re_clean_whitespace.sub("]]", self.file.read())
      self.lineno = 0
      self.functions = {}
      self.tree = TopLevelTemplateNode(self)

   def parser_get(self):
      if self.line == '':
         return None
      return self.line

   def parser_eat(self, chars):
      self.lineno = self.lineno + self.line[:chars].count("\n")
      self.line = self.line[chars:]

   def parser_exception(self, s, e=None):
      import traceback
      if e is not None:
         traceback.print_exc()
      raise ParserException(self.lineno, s)

   def execute_file(self, filename, data={}):
      output = self.execute_string(data)
      file = open(filename, 'w')
      file.write(output)
      file.write("\n")
      file.close()

   def execute_string(self, data={}):
      data_copy = {}
      data_copy.update(data)
      s = io.StringIO()
      self.execute(s, data_copy)
      s.write("\n")
      return s.getvalue()

   def execute_stdout(self, data={}):
      data_copy = {}
      data_copy.update(data)
      self.execute(sys.stdout, data_copy)
      sys.stdout.write("\n")

   def execute(self, stream=sys.stdout, data={}):
      self.tree.execute(stream, data)

   def __repr__(self):
      return repr(self.tree)


############################################################
# NODES
class TemplateNode:
   def __init__(self, parent, s):
      self.parent = parent
      self.s = s
      self.node_list = []
      while 1:
         new_node = TemplateNodeFactory(parent)
         if self.add_node(new_node):
            break

   def add_node(self, node):
      if node == 'end':
         return 1
      elif node is not None:
         self.node_list.append(node)
      else:
         raise self.parent.parser_exception(
           "[[%s]] does not have a matching [[end]]" % self.s)

   def execute(self, stream, data):
      for node in self.node_list:
         node.execute(stream, data)

   def __repr__(self):
      r = "<" + self.__class__.__name__ + " "
      for i in self.node_list:
         r = r + repr(i)
      r = r + ">"
      return r

class TopLevelTemplateNode(TemplateNode):
   def __init__(self, parent):
      TemplateNode.__init__(self, parent, '')

   def add_node(self, node):
      if node is not None:
         self.node_list.append(node)
      else:
         return 1

class ForTemplateNode(TemplateNode):
   def __init__(self, parent, s):
      TemplateNode.__init__(self, parent, s)
      match = re_for_loop.match(s)
      if match is None:
         raise self.parent.parser_exception(
           "[[%s]] is not a valid for-loop expression" % self.s)
      else:
         self.vars_temp = match.group(1).split(",")
         self.vars = []
         for v in self.vars_temp:
            self.vars.append(v.strip())
         self.expression = match.group(2)

   def execute(self, stream, data):
      remember_vars = {}
      for var in self.vars:
         if var in data:
            remember_vars[var] = data[var]
      try:
         x = eval(self.expression, globals(), data)
      except Exception as e:
         self.parent.parser_exception(self.expression, e)
      for list in x:
         if util.is_sequence(list):
            if len(self.vars) == 1:
               data[self.vars[0]] = list
            elif len(self.vars) == len(list):
               for index, value in util.enumerate(list):
                  data[self.vars[index]] = value
            else:
               self.parent.parser_exception(
                 "Unable to unpack tuples in [[%s]]" % self.s)
         else:
            data[self.vars[0]] = list
         TemplateNode.execute(self, stream, data)
      for key, value in remember_vars.items():
         data[key] = value

class IfTemplateNode(TemplateNode):
   def __init__(self, parent, s):
      self.else_node = None
      TemplateNode.__init__(self, parent, s)
      match = re_if.match(s)
      if match is None:
         raise self.parent.parser_exception(
           "[[%s]] is not a valid if expression" % self.s)
      else:
         self.expression = match.group(1)

   def add_node(self, node):
      if node == 'end':
         return 1
      elif isinstance(node, ElseTemplateNode):
         self.else_node = node
         return 1
      elif isinstance(node, ElifTemplateNode):
         self.else_node = node
         return 1
      elif node is not None:
         self.node_list.append(node)
      else:
         raise self.parent.parser_exception(
           "[[%s]] does not have a matching [[end]]" % self.s)

   def execute(self, stream, data):
      try:
         x = eval(self.expression, globals(), data)
      except Exception as e:
         self.parent.parser_exception(self.expression, e)
      if x:
         TemplateNode.execute(self, stream, data)
      elif self.else_node is not None:
         self.else_node.execute(stream, data)

class ElifTemplateNode(IfTemplateNode):
   def __init__(self, parent, s):
      self.else_node = None
      TemplateNode.__init__(self, parent, s)
      match = re_elif.match(s)
      if match is None:
         self.parent.parser_exception(
           "[[%s]] is not a valid elif expression" % self.s)
      else:
         self.expression = match.group(1)

class ElseTemplateNode(TemplateNode):
   pass

class FunctionTemplateNode(TemplateNode):
   def __init__(self, parent, s):
      TemplateNode.__init__(self, parent, s)
      match = re_def.match(s)
      if match is None:
         self.parent.parser_exception(
           "[[%s]] is not a valid function definition" % self.s)
      self.function_name = match.group(1)
      self.vars_temp = match.group(2).split(",")
      self.vars = []
      for v in self.vars_temp:
         self.vars.append(v.strip())
      self.parent.functions[self.function_name] = self

   def execute(self, stream, data):
      pass

   def call(self, args, stream, data):
      remember_vars = {}
      for index, var in util.enumerate(self.vars):
         if var in data:
            remember_vars[var] = data[var]
         data[var] = args[index]
      TemplateNode.execute(self, stream, data)
      for key, value in remember_vars.items():
         data[key] = value

class LeafTemplateNode(TemplateNode):
   def __init__(self, parent, s):
      self.parent = parent
      self.s = s

   def execute(self, stream, data):
      stream.write(self.s)

   def __repr__(self):
      return "<" + self.__class__.__name__ + ">"

class CommentTemplateNode(LeafTemplateNode):
   def execute(self, stream, data):
      pass

class ExpressionTemplateNode(LeafTemplateNode):
   def execute(self, stream, data):
      try:
         tmp = str(eval(self.s, globals(), data))
         tmp = u"" + tmp
         stream.write(tmp)
      except Exception as e:
         self.parent.parser_exception(self.s, e)

class ExecTemplateNode(LeafTemplateNode):
   def __init__(self, parent, s):
      LeafTemplateNode.__init__(self, parent, s)
      match = re_exec.match(s)
      if match is None:
         self.parent.parser_exception(
           "[[%s]] is not a valid statement" % self.s)
      self.s = match.group(1)

   def execute(self, stream, data):
      try:
         exec(self.s, globals(), data)
      except Exception as e:
         self.parent.parser_exception(self.s, e)

class CallTemplateNode(LeafTemplateNode):
   def __init__(self, parent, s):
      LeafTemplateNode.__init__(self, parent, s)
      match = re_call.match(s)
      if match is None:
         self.parent.parser_exception(
           "[[%s]] is not a valid function call" % self.s)
      self.function_name = match.group(1)
      self.vars = "(" + match.group(2).strip() + ",)"

   def execute(self, stream, data):
      try:
         x = eval(self.vars, globals(), data)
      except Exception as e:
         self.parent.parser_exception(self.vars, e)
      self.parent.functions[self.function_name].call(
        x, stream, data)


############################################################
# Node factory
template_factory_type_map = {
  'if'   : IfTemplateNode,
  'for'  : ForTemplateNode,
  'elif' : ElifTemplateNode,
  'else' : ElseTemplateNode,
  'def'  : FunctionTemplateNode,
  'call' : CallTemplateNode,
  'exec' : ExecTemplateNode }
template_factory_types = list(template_factory_type_map.keys())

def TemplateNodeFactory(parent):
   src = parent.parser_get()

   if src is None:
      return None
   match = re_directive.search(src)
   if match is None:
      parent.parser_eat(len(src))
      return LeafTemplateNode(parent, src)
   elif src == '' or match.start() != 0:
      parent.parser_eat(match.start())
      return LeafTemplateNode(parent, src[:match.start()])
   else:
      directive = match.group()[2:-2].strip()
      parent.parser_eat(match.end())
      if directive == 'end':
         return 'end'
      elif re_comment.match(directive):
         return CommentTemplateNode(parent, directive)
      else:
         for i in template_factory_types:
            if directive[0:len(i)] == i:
               return template_factory_type_map[i](parent, directive)
         return ExpressionTemplateNode(parent, directive)


############################################################
# TESTING CODE
if __name__ == '__main__':
   combinations = (('OneBit', 'Float', 'GreyScale'),
                   ('GreyScale', 'RGB'))

   template = Template("""
   [[# This is a comment #]]
   [[# This example does recursive function calls need to generate feature combinations #]]
   [[def switch(layer, args)]]
      switch(m[[layer]].id) {
      [[for option in combinations[layer] ]]
      [[exec current = option + '(m' + str(layer) + ')']]
      case [[option]]:
        [[if layer == layers - 1]]
          function_call([[string.join(args + [current], ',')]]);
        [[else]]
          [[call switch(layer + 1, args + [current])]]
        [[end]]
      break;
      [[end]]
      }
   [[end]]

   PyObject *py_overload_resolution_[[function_name]](PyObject *args) {
   [[call switch(0, [])]]
   }
   """)

   data = {'combinations'  : combinations,
           'function_name' : 'threshold',
           'layers'        : 2}
   template.execute(sys.stdout, data)
