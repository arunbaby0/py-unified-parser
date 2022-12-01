import pkgutil
from typing import Optional

v = pkgutil.get_data(__name__, "final-release.version")
__version__: Optional[str]
if v is not None:
    __version__ = v.decode().strip()
else:
    __version__ = None
