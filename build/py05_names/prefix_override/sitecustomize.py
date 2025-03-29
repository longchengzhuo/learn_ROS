import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/cl/CLionProjects/ws01_plumbing/install/py05_names'
