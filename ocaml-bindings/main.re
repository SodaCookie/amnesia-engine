/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

let arrayOfPolygons = ref [];

for j in 0 to 5 {
  for i in 0 to 8 {
    let deltaY = float_of_int (i * 140);
    let deltaX = float_of_int (j * 200);
    arrayOfPolygons := [
      Polygon.create_polygon [
        Vector.create_vector deltaX (0. +. deltaY),
        Vector.create_vector deltaX (100. +. deltaY),
        Vector.create_vector (deltaX +. 20.) (100. +. deltaY),
        Vector.create_vector (deltaX +. 20.) (0. +. deltaY)
      ],
      ...!arrayOfPolygons
    ]
  }
};

let bl2 = Vector.create_vector 0. 0.;

let tl2 = Vector.create_vector 0. 1000.;

let tr2 = Vector.create_vector 1000. 1000.;

let br2 = Vector.create_vector 1000. 0.;

let view = Polygon.create_polygon [bl2, tl2, tr2, br2];

let windowSize = 1000;

let windowSizef = float_of_int windowSize;

type floatPointType = {x: float, y: float};

type wCoordType = | WCoord of Vector.vectorT;

type gCoordType = | GCoord of floatPointType;

type gameStateT = {light: Lightsource.lightsourceT, light2: Lightsource.lightsourceT};

let toWorldCoord (WCoord {Vector.x: x, Vector.y: y}) => (
  x /. (windowSizef /. 2.) -. 1.,
  y /. (windowSizef /. 2.) -. 1.
);

let drawPolygon alpha::alpha=1. filled::filled polygon::polygon color::color => {
  let open Polygon;
  if filled {
    GlDraw.begins `polygon
  } else {
    GlDraw.begins `line_loop
  };
  GlDraw.color alpha::alpha color;
  List.iter GlDraw.vertex2 (List.map (fun v => toWorldCoord (WCoord v)) polygon.vertices);
  GlDraw.ends ()
};

let drawCircle alpha::alpha=1. radius::radius color::color position::(GCoord {x, y}) => {
  let deg2grad = 3.14159 /. 180.;
  let floatRadius = float_of_int radius;
  GlDraw.begins `triangle_fan;
  GlDraw.color alpha::alpha color;
  for i in 0 to 360 {
    let degInGrad = float_of_int i *. deg2grad;
    GlDraw.vertex2 @@
      toWorldCoord (
        WCoord Vector.{x: cos degInGrad *. floatRadius +. x, y: sin degInGrad *. floatRadius +. y}
      )
  };
  GlDraw.ends ()
};

let mouseDidMove gameState::gameState x::x y::y =>
  Lightsource.move_lightsource
    gameState.light (Vector.create_vector (float_of_int x) (float_of_int (windowSize - y)));

let numOfPoints = ref 0;

let prevTime = ref 0.;

let createLightsourceTime = ref 0.;

let processTime = ref 0.;
let render gameState::gameState () => {
  GlClear.clear [`color];
  GlMat.load_identity ();
  let prevTime = Unix.gettimeofday ();
  let polygonList =
    Lightsource.process lightsource::gameState.light objects::!arrayOfPolygons view::view;
  let polygonList2 =
    Lightsource.process lightsource::gameState.light2 objects::!arrayOfPolygons view::view;
print_endline @@ "process time: " ^ (string_of_float (!processTime));
  processTime := Unix.gettimeofday () -. prevTime;
  drawPolygon alpha::0.7 filled::true polygon::view color::(0., 0., 0.);
  ignore @@
    List.map
      (fun p => drawPolygon alpha::0.7 filled::true polygon::p color::(1., 1., 1.)) polygonList;
  ignore @@
    List.map
      (fun p => drawPolygon alpha::0.7 filled::true polygon::p color::(1., 1., 1.)) polygonList2;
  /* ignore @@
       List.map
         (fun p => drawPolygon alpha::1. filled::false polygon::p color::(0., 1., 0.)) polygonList;
     ignore @@
       List.map
         (fun p => drawPolygon alpha::1. filled::false polygon::p color::(0., 1., 0.)) polygonList2; */
  Vector.(
    Lightsource.(
      drawCircle
        alpha::1.
        radius::4
        color::(1., 0., 0.)
        position::(GCoord {x: gameState.light.position.x, y: gameState.light.position.y})
    )
  );
  Vector.(
    Lightsource.(
      drawCircle
        alpha::1.
        radius::4
        color::(1., 0., 0.)
        position::(GCoord {x: gameState.light2.position.x, y: gameState.light2.position.y})
    )
  );
  Glut.swapBuffers ()
};

Glut.init Sys.argv;

Glut.initWindowSize windowSize windowSize;

Glut.initDisplayMode double_buffer::true ();

Glut.createWindow title::"Lights and Shadows";

let gameState = {
  light: Lightsource.create_lightsource (Vector.create_vector 100. 50.) 400. 1.,
  light2: Lightsource.create_lightsource (Vector.create_vector 300. 50.) 400. 1.
};

/* Glut.passiveMotionFunc (mouseDidMove gameState::gameState); */
GlMat.mode `modelview;

Glut.displayFunc (render gameState::gameState);

let sign = ref false;

let x = ref 100;

let y = ref 50;

let prevX = ref 0;

Glut.idleFunc
  cb::(
    Some (
      fun () => {
        if (!x <= 900) {
          if (!sign && !y <= 50 || not !sign && !y >= 870) {
            if (!x >= !prevX + 200) {
              sign := not !sign
            } else {
              x := !x + 5
            }
          } else {
            prevX := !x;
            if !sign {
              y := !y - 5
            } else {
              y := !y + 5
            }
          };
          Lightsource.move_lightsource
            gameState.light
            (Vector.create_vector (float_of_int !x) (float_of_int (windowSize - !y)));
          Lightsource.move_lightsource
            gameState.light2
            (Vector.create_vector (float_of_int (!x + 200)) (float_of_int (windowSize - !y)))
        };
        Glut.postRedisplay ()
      }
    )
  );

Glut.mainLoop ();
