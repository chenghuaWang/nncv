import sys
import json
import argparse


def __solve_packages_antlr__():
    # download antlr-complete.jar
    # download cpp runtime
    pass


__nncv_solve_availiable_packages__ = {{"antlr": __solve_packages_antlr__}}

parser = argparse.ArgumentParser(description="NNCV Build Helper")
parser.add_argument(
    "solve-third-party", type=str, help="The package you want to install"
)


if __name__ == "__main__":
    pass
