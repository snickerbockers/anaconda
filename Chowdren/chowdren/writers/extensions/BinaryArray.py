# Copyright (c) Mathias Kaerlev 2012-2015.
#
# This file is part of Anaconda.
#
# Anaconda is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Anaconda is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Anaconda.  If not, see <http://www.gnu.org/licenses/>.

from chowdren.writers.objects import ObjectWriter

from chowdren.common import get_animation_name, to_c, make_color

from chowdren.writers.events import (ComparisonWriter, ActionMethodWriter,
    ConditionMethodWriter, ExpressionMethodWriter, make_table)

class BinaryArray(ObjectWriter):
    class_name = 'BinaryArray'
    filename = 'binaryarray'

    def write_init(self, writer):
        pass

actions = make_table(ActionMethodWriter, {
    0 : 'load_file',
    2 : 'load_workspaces',
    12 : 'create_workspace',
    4 : 'switch_workspace',

})

conditions = make_table(ConditionMethodWriter, {
    0 : 'has_workspace'
})

expressions = make_table(ExpressionMethodWriter, {
    10 : 'get_size',
    3 : 'read_string'
})

def get_object():
    return BinaryArray