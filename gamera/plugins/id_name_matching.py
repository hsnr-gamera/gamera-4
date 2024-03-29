#
# Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom,
#                          and Karl MacMillan
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


from gamera.plugin import * 
import re, string


def build_id_regex(s):
    def _build_id_regex_parts(s):
        if s == '':
            return ''
        regex_parts = []
        parts = s.split('.')
        for part in parts:
            ors = part.split('|')
            l = []
            for part0 in ors:
                part0 = part0.replace('*', '[^.]*')
                part0 = part0.replace('?', '[^.]')
                l.append(part0)
            regex_parts.append('(?:%s)' % '|'.join(['(?:%s)' % x for x in l]))
        regex = r'\.'.join(regex_parts)
        return regex

    def _build_id_regex_parens(s):
        lparen = s.find('(')
        rparen = s.find(')')
        if s == '':
            return '', ''
        elif s[0] == '|':
            r, s = _build_id_regex_parens(s[1:])
            return '|' + r, s
        elif lparen != -1 and lparen < rparen:
            result = _build_id_regex_parts(s[:lparen])
            r1, s1 = _build_id_regex_parens(s[lparen+1:])
            r2, s2 = _build_id_regex_parens(s1)
            return result + r1 + r2, s2
        elif rparen != -1:
            return _build_id_regex_parts(s[:rparen]), s[rparen+1:]
        else:
            return _build_id_regex_parts(s), ''
    regex, s = _build_id_regex_parens(s)
    return re.compile(regex, re.IGNORECASE)

regex_cache = {}
dummy_regex = re.compile('')
type_dummy_regex = type(dummy_regex)
class match_id_name(PluginFunction):
    r"""
    Returns true if the image's main ``id_name`` matches the given regular
    expression.

    *regex*
      A special-purpose regular expression as defined below.

    A special-purpose regular expression language designed for
    convenience on Gamera symbol names is used here.  It has limited
    flexibility relative to Python regular expressions, and is more
    akin to wildcards in command-line shells.  This language is
    converted to standard Python regular expressions (``re`` module)
    for efficiency.

    **Informal syntax definition:**

    ====================  =============================================
    Regular expression    Description
    ====================  =============================================
    ``A|B``               matches ``A`` or ``B``
    ``A.B|C``             matches ``A.B`` or ``A.C``
    ``*``                 multiple-character wildcard
    ``?``                 single character wildcard
    ``()``                grouping can be performed with parentheses
    ``[a-z]``             matches any character a-z
    ====================  =============================================
    
    **Example expressions:**
    
    ========================  ====================================================  
    ``(upper.x)|(lower.y)``   match either ``upper.x`` or ``lower.y``
    ``upper.x|upper.y``       careful! matches ``upper.x.y`` or ``upper.upper.y``
    ``upper.*``               match anything in the ``upper`` category
    ``upper.a|b|c``           matches ``upper.a``, ``upper.b`` or ``upper.c``
    ``upper.capital_?``       ``?`` is a single character wildcard
    ========================  ====================================================
    """
    args = Args([String('regex')])
    def __call__(self, regex):
        global regex_cache
        if util.is_string_or_unicode(regex):
            compiled = regex_cache.get(regex, None)
            if compiled is None:
                compiled = build_id_regex(regex)
                regex_cache[regex] = compiled
        elif type(regex) == type_dummy_regex:
            compiled = regex
        else:
            raise TypeError(
                "Expression must be a string or a compiled Python regular expression.")
        name = self.get_main_id()
        if compiled.match(name):
            return 1
        #for confidence, name in self.id_name:
        #    if compiled.match(name):
        #        return 1
        return 0
    __call__ = staticmethod(__call__)

_valid = string.ascii_letters + string.digits + "_"
def id_name_to_identifier(symbol):
    while len(symbol) and symbol[0] == '.':
        symbol = symbol[1:]
    if symbol == '':
        return '____'
    def translate(c):
        if not c in _valid:
            return "_"
        return c
    symbol = ''.join([translate(x) for x in symbol])
    symbol = symbol.lower()
    if symbol[0] in string.digits or keyword.iskeyword(symbol):
        symbol = '_' + symbol + '_'
    # Split by '.' delimiters
    orig_tokens = symbol.strip().split('.')
    tokens = []
    for token in orig_tokens:
        if token.strip() != '':
            tokens.append(token.strip())
    symbol = '_'.join(tokens)
    return symbol

class IdNameMatchingModule(PluginModule):
    category = "Classification"
    functions = [match_id_name]
    author = "Michael Droettboom and Karl MacMillan"
    url = "http://gamera.sourceforge.net/"
    pure_python = 1

module = IdNameMatchingModule()

match_id_name = match_id_name()
