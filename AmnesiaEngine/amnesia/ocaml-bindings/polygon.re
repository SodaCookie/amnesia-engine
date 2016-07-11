
type polygonT = {vertices: list Vector.vectorT};

external create_polygon : list Vector.vectorT => polygonT = "polygon_create_polygon";

let to_string p =>
  "[" ^
    List.fold_left
      (fun acc x => acc ^ ", " ^ Vector.to_string x)
      (Vector.to_string (List.hd p.vertices))
      (List.tl p.vertices) ^
    "]";
