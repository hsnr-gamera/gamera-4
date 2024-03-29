# -*- mode: python; indent-tabs-mode: nil; tab-width: 4 -*-
# vim: set tabstop=4 shiftwidth=4 expandtab:
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

import string, keyword
from gamera import util

class SymbolTable(util.CallbackObject):
   def __init__(self):
      util.CallbackObject.__init__(self)
      self.symbols = {}
      self.add("skip", 0)

   ########################################
   # CALLBACKS

   def add_callback(self, alert, callback):
      util.CallbackObject.add_callback(self, alert, callback)
      if alert == "add":
         for symbol in list(self.symbols.keys()):
            callback(self.normalize_symbol(symbol)[1])

   ########################################

   def normalize_symbol(self, symbol):
      # assert type(symbol) == types.StringType
      while len(symbol) and symbol[0] == '.':
         symbol = symbol[1:]
      if symbol == '':
         return '', []
      symbol = symbol.lower()
      if type(symbol) == str:
         orig_tokens = symbol.strip().split('.')
      else:
         orig_tokens = symbol.strip().split(b'.')
      tokens = []
      for token in orig_tokens:
         if token.strip() != '':
            tokens.append(token.strip())
      if type(symbol) == str:
         symbol = '.'.join(tokens)
      else:
         symbol = b'.'.join(tokens)
      return symbol, tokens

   def add(self, symbol, id = -1):
      symbol, tokens = self.normalize_symbol(symbol)
      if symbol in self.symbols:
         return symbol
      self.symbols[symbol] = None
      self.trigger_callback('add', tokens)
      return symbol

   def remove(self, symbol):
      symbol, tokens = self.normalize_symbol(symbol)
      if symbol in self.symbols:
         del self.symbols[symbol]
         self.trigger_callback('remove', tokens)
         return 1
      return 0

   def autocomplete(self, symbol):
      targets = list(self.symbols.keys())
      targets.sort()
      found_i = -1
      for i in range(len(targets)):
         if targets[i].startswith(symbol):
            found_i = i
            break
      if found_i != -1:
         found = targets[found_i]
         if found_i < len(targets) - 1:
            found_last = -1
            for i in range(found_i + 1, len(targets)):
               if targets[i].startswith(symbol):
                  found_last = i
               else:
                  break
            if found_last != -1:
               found_last = targets[found_last]
               found_it = 0
               for i in range(len(symbol), min(len(found), len(found_last))):
                  if found[i] != found_last[i]:
                     found_it = 1
                     break
               if found_it:
                  found = found[:i]
         return found
      return symbol

   def exists(self, symbol):
      return symbol in self.symbols

