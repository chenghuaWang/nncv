"""
config.py

Placing all config parameters here.
"""
NNCV_CFG = {
    # exec file path
    "NNCV_COMPILER_BIN": "/bin/nncv-c",
    "NNCV_RUNNER_BIN": "/bin/nncv-c",
    # compiler config file. default=None
    # you can specific a .yaml file when run nncv.compile(..., file_path)
    "COMPILER_CONFIG": None,

}
