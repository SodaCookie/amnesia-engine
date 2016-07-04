/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

open Vector;

let bl = create_vector 100. 100.;

let tl = create_vector 100. 200.;

let tr = create_vector 200. 200.;

let br = create_vector 200. 100.;

let poly1 = Polygon.create_polygon [bl, tl, tr, br];

let bl2 = create_vector 0. 0.;

let tl2 = create_vector 0. 800.;

let tr2 = create_vector 800. 800.;

let br2 = create_vector 800. 0.;

let view = Polygon.create_polygon [bl2, tl2, tr2, br2];

let windowSize = 800;

let windowSizef = float_of_int windowSize;

type floatPointType = {x: float, y: float};

type intPointType = {x: int, y: int};

type wCoordType = | WCoord of floatPointType;

type gCoordType = | GCoord of intPointType;

type pCoordType = | PCoord of intPointType;

type gameStateT = {mutable mousePos: gCoordType};

let toWorldCoord (WCoord {x, y}) => (
  x /. (windowSizef /. 2.) -. 1.,
  y /. (windowSizef /. 2.) -. 1.
);

let drawPolygon polygon::polygon color::color => {
  GlDraw.begins `polygon;
  GlDraw.color color;
  let vectorList = Polygon.get_vertices polygon;
  List.iter
    GlDraw.vertex2
    (List.map (fun v => toWorldCoord (WCoord {x: Vector.get_x v, y: Vector.get_y v})) vectorList);
  GlDraw.ends ()
};

let mouseDidMove gameState::gameState x::x y::y => {
  let mousePos = GCoord {x, y: windowSize - y};
  gameState.mousePos = mousePos
};

let render gameState::gameState () => {
  GlClear.clear [`color];
  GlMat.load_identity ();
  let GCoord {x, y} = gameState.mousePos;
  let light =
    Lightsource.create_lightsource (create_vector (float_of_int x) (float_of_int y)) 200. 1.;
  let polygonList = Lightsource.process lightsource::light objects::[poly1] view::view;
  ignore @@ List.map (fun p => drawPolygon polygon::p color::(1., 1., 1.)) polygonList;
  Glut.swapBuffers ()
};

Glut.init Sys.argv;

Glut.initWindowSize windowSize windowSize;

Glut.initDisplayMode double_buffer::true ();

Glut.createWindow title::"Lights and Shadows";

let gameState = {mousePos: GCoord {x: 320, y: 280}};

Glut.passiveMotionFunc (mouseDidMove gameState::gameState);

GlMat.mode `modelview;

Glut.displayFunc (render gameState::gameState);

Glut.idleFunc cb::(Some Glut.postRedisplay);

Glut.mainLoop ();
