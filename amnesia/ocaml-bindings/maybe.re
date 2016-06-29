
open Ctypes;

open Foreign;

type maybeT;

let maybeT: typ (structure maybeT) = structure "Maybe";

let unwrap = foreign "unwrap" (ptr maybeT @-> returning (ptr Vector.vectorT));

let should_unwrap = foreign "should_unwrap" (ptr maybeT @-> returning bool);

let wrap v => {
  if (should_unwrap v) {
    Some (unwrap v)
  } else {
    None
  }
};
