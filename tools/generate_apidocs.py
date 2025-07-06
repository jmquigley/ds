#!/usr/bin/env python

"""
This script generates API documentation files that can be used with
Sphinx and the Breathe api.  The Breathe API links Doxygen and Sphinx
together, so that Doxygen generated files can be used in Sphinx.
Restructured text documents still need to exist to use what is created
by Breathe. This script will generate the stubs needed by each c++
class.
"""
import argparse
import logging
import os
from os.path import abspath, dirname, exists, join, realpath
import shutil
import sys

logformat = '%(asctime)s [%(levelname)7s]: %(message)s'
logging.basicConfig(level=logging.DEBUG, stream=sys.stdout, format=logformat)
log = logging.getLogger(__name__)


class App(object):

    def __init__(self, args):
        self._args = args
        log.debug(f"args: {self._args}")

        # Retrieve the list of all classes that should be documented
        filelist = abspath(join(args.prefix, args.input))
        self._classList = self.readFileList(filelist);
        dst = abspath(join(args.prefix, args.directory))
        self._classList = [join(dst, x) + ".rst" for x in self._classList]
        log.debug(f"class list: {self._classList}")

    def readFileList(self, filename, prefix=""):
        lines = []

        with open(filename, "r") as inp:
            for line in inp:
                line = line.strip()
                if line != "" and not line.startswith("#"):
                    lines.append(prefix + line)

        return lines

    def main(self):
        log.debug("Running main()")

        nl = os.linesep
        ns = self._args.namespace
        project = self._args.project
        ch = "*"

        for filename in self._classList:
            with open(filename, "w") as f:
                log.debug(f"processing: {filename}")
                klass = os.path.splitext(os.path.basename(filename))[0]
                n = len(klass)
                print(f"{ch * n}", file=f)
                print(f"{klass}", file=f)
                print(f"{ch * n}{nl}", file=f)
                print(f".. doxygenclass:: {ns}{klass}", file=f)
                print(f"   :project: {project}{nl}", file=f)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--directory", "-d",
        required=False,
        default="docs/api/",
        help="The output directory where the API files will be created"
    )

    parser.add_argument(
        "--input", "-i",
        required=False,
        default="docs/reflist.in",
        help="The list of class names that will be generated into API documents"
    )

    parser.add_argument(
        "--namespace", "-n",
        required=False,
        default="ds::",
        help="The namespace used within the c++ API"
    )

    parser.add_argument(
        "--prefix",
        required=False,
        default="/root/workspace/ds/",
        help="The root prefix directory where project files can be found"
    )

    parser.add_argument(
        "--project",
        required=False,
        default="ds",
        help="The name of the project"
    )

    cliargs = parser.parse_args()

    log.info("Creating API document files")
    App(cliargs).main()
    log.info("Done.")
