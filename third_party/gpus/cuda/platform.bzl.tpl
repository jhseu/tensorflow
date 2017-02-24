CUDA_VERSION = "%{cuda_version}"
CUDNN_VERSION = "%{cudnn_version}"
CUDART_DIR = "%{cudart_dir}"
PLATFORM = "%{platform}"

def cuda_sdk_version():
  return CUDA_VERSION

def cudnn_sdk_version():
  return CUDNN_VERSION

def cudart_dir():
  return CUDART_DIR

def readlink_command():
  if PLATFORM == "Darwin":
    return "greadlink"
  else:
    return "readlink"
