
type lightsourceT = {position: Vector.vectorT, radius: float, strength: float};

external create_lightsource : Vector.vectorT => float => float => lightsourceT = "lightsource_create_lightsource";

external move_lightsource : lightsourceT => Vector.vectorT => unit = "lightsource_move_lightsource";

external process : lightsource::lightsourceT =>
                   objects::list Polygon.polygonT =>
                   view::Polygon.polygonT =>
                   list Polygon.polygonT = "lightsource_process";
