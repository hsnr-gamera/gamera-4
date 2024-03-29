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

from gamera.gui import has_gui

if has_gui.has_gui:
   from gamera.gui import gui
   CustomMenu = gui.CustomMenu
   from gamera.gui import icon_display
   CustomIcon = icon_display.CustomIcon
else:
   class NullClass:
      def __init__(self, *args, **kwargs):
         pass
   class CustomMenu(NullClass):
      pass
   class CustomIcon(NullClass):
      def register(cls, *args, **kwargs):
         pass
      register = classmethod(register)

__all__ = "CustomMenu CustomIcon".split()
