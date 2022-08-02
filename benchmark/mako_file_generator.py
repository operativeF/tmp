#!/usr/bin/env python3

import sys
from mako.template import Template

def create_rendered_file(mako_template, cpp_target_file, type_iterations):
    cpp_file = open(cpp_target_file, 'w')
    write_cpp_file = lambda cpp_code: cpp_file.write(cpp_code)
    temp_file = Template(filename=mako_template)
    code = temp_file.render(iterations=type_iterations)
    write_cpp_file(code)
    cpp_file.close()

create_rendered_file("Boost.TMP-Bench.Clamp.cpp.mako", "Boost.TMP-Bench.Clamp.cpp", 1000)
