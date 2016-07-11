/*
 * vim: set ft=rust:
 * vim: set ft=reason:
 */

let a = Vector.create_vector 1. 1.;

let b = Vector.create_vector 1. 0.;

let b2 = Vector.create_vector 0. 1.;

let b3 = Vector.rotate b2 3.14159265358;

print_endline @@ (Vector.to_string b3 ^ " - " ^ Vector.(to_string (normalized a + a)));

switch (
  Segment.intersect_line
    (Segment.create_segment (Vector.create_vector 0. 0.) (Vector.create_vector 1. 0.))
    (Segment.create_segment (Vector.create_vector 0. 0.) (Vector.create_vector 0. 1.))
) {
| None => print_endline "sadness"
| Some v => print_endline @@ Vector.to_string v
};

/* open Vector;

   let arrayOfPolygons = ref [];

   for j in 0 to 5 {
     for i in 0 to 8 {
       let deltaY = float_of_int (i * 140);
       let deltaX = float_of_int (j * 200);
       arrayOfPolygons := [
         Polygon.create_polygon [
           create_vector deltaX (0. +. deltaY),
           create_vector deltaX (100. +. deltaY),
           create_vector (deltaX +. 20.) (100. +. deltaY),
           create_vector (deltaX +. 20.) (0. +. deltaY)
         ],
         ...!arrayOfPolygons
       ]
     }
   };

   let bl2 = create_vector 0. 0.;

   let tl2 = create_vector 0. 1000.;

   let tr2 = create_vector 1000. 1000.;

   let br2 = create_vector 1000. 0.;

   let view = Polygon.create_polygon [bl2, tl2, tr2, br2];

   let windowSize = 1000;

   let windowSizef = float_of_int windowSize;

   type floatPointType = {x: float, y: float};

   type intPointType = {x: int, y: int};

   type wCoordType = | WCoord of floatPointType;

   type gCoordType = | GCoord of intPointType;

   type pCoordType = | PCoord of intPointType;

   type gameStateT = {mutable lightPos: gCoordType};

   let toWorldCoord (WCoord {x, y}) => (
     x /. (windowSizef /. 2.) -. 1.,
     y /. (windowSizef /. 2.) -. 1.
   );

   let drawPolygon filled::filled polygon::polygon color::color => {
     if filled {
       GlDraw.begins `polygon
     } else {
       GlDraw.begins `line_loop
     };
     GlDraw.color color;
     let vectorList = Polygon.get_vertices polygon;
     List.iter
       GlDraw.vertex2
       (List.map (fun v => toWorldCoord (WCoord {x: Vector.get_x v, y: Vector.get_y v})) vectorList);
     GlDraw.ends ()
   };

   let drawCircle radius::radius color::color position::(GCoord {x, y}) => {
     let deg2grad = 3.14159 /. 180.;
     let floatRadius = float_of_int radius;
     GlDraw.begins `triangle_fan;
     GlDraw.color color;
     for i in 0 to 360 {
       let degInGrad = float_of_int i *. deg2grad;
       GlDraw.vertex2 @@
         toWorldCoord (
           WCoord {
             x: cos degInGrad *. floatRadius +. float_of_int x,
             y: sin degInGrad *. floatRadius +. float_of_int y
           }
         )
     };
     GlDraw.ends ()
   };

   let mouseDidMove gameState::gameState x::x y::y => {
     let lightPos = GCoord {x, y: windowSize - y};
     gameState.lightPos = lightPos
   };

   let numOfPoints = ref 0;

   let prevTime = ref 0.;

   let createLightsourceTime = ref 0.;

   /* let processTime = ref 0.; */

   let render gameState::gameState () => {
     let curTime = Unix.gettimeofday ();
     numOfPoints := !numOfPoints + 1;
     if (curTime -. !prevTime >= 1.) {
       print_endline @@ ("framerate -> " ^ string_of_int !numOfPoints);
       print_endline @@ "average create_lightsource time: " ^ (string_of_float (!createLightsourceTime /. (float_of_int !numOfPoints)));
       /* print_endline @@ "average process time: " ^ (string_of_float (!processTime /. (float_of_int !numOfPoints))); */
       numOfPoints := 0;
       /* processTime := 0.; */
       createLightsourceTime := 0.;
       prevTime := curTime;
     };
     GlClear.clear [`color];
     GlMat.load_identity ();
     let GCoord {x, y} = gameState.lightPos;
     let prevTime = Unix.gettimeofday ();
     let light =
       Lightsource.create_lightsource (create_vector (float_of_int x) (float_of_int y)) 200. 1.;
     createLightsourceTime := !createLightsourceTime +. (Unix.gettimeofday () -. prevTime);
     let light2 =
        Lightsource.create_lightsource
          (create_vector (float_of_int (x + 300)) (float_of_int y)) 200. 1.;
     /* let prevTime = Unix.gettimeofday (); */
     let polygonList = Lightsource.process lightsource::light objects::!arrayOfPolygons view::view;
     /* processTime := !processTime +. (Unix.gettimeofday () -. prevTime); */
     let polygonList2 = Lightsource.process lightsource::light2 objects::!arrayOfPolygons view::view;
     ignore @@ List.map (fun p => drawPolygon filled::true polygon::p color::(1., 1., 1.)) polygonList;
     ignore @@
        List.map (fun p => drawPolygon filled::true polygon::p color::(1., 1., 1.)) polygonList2;
     ignore @@
       List.map (fun p => drawPolygon filled::false polygon::p color::(0., 1., 0.)) polygonList;
     ignore @@
        List.map (fun p => drawPolygon filled::false polygon::p color::(0., 1., 0.)) polygonList2;
     drawCircle radius::4 color::(1., 0., 0.) position::(GCoord {x, y});
     drawCircle radius::4 color::(1., 0., 0.) position::(GCoord {x: x + 300, y});
     Glut.swapBuffers ()
   };

   Glut.init Sys.argv;

   Glut.initWindowSize windowSize windowSize;

   Glut.initDisplayMode double_buffer::true ();

   Glut.createWindow title::"Lights and Shadows";

   let gameState = {lightPos: GCoord {x: 100, y: 50}};

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
             gameState.lightPos = GCoord {x: !x, y: windowSize - !y}
           };
           Glut.postRedisplay ()
         }
       )
     );

   Glut.mainLoop (); */
