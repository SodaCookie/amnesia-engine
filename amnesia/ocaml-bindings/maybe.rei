
open Ctypes;

type maybeT;

let maybeT: typ (structure maybeT);

let wrap:
  Ctypes_static.ptr (Ctypes.structure maybeT) =>
  option (Ctypes_static.ptr (Ctypes.structure Vector.vectorT));
