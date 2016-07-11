INCLUDES=-I`ocamlc -where`

app.out: _build main.cmo vector.cmo maybe.cmo segment.cmo polygon.cmo libvector.so libpolygon.so liblightsource.so libmaybe.so libsegment.so
	  ocamlfind ocamlc -o _build/app.out -cc clang++ -ccopt '-lc++ --std=c++11 -stdlib=libc++' -I _build -I ../../_build -linkpkg -custom -package ctypes.foreign -package lablgl.glut \
	    -cclib -L. -cclib -lvector -cclib -lsegment -cclib -lmaybe -cclib -lpolygon -cclib -llightsource -cclib -lSDL2 \
			../../_build/libamnesia.a  \
			_build/vector.cmo _build/maybe.cmo _build/segment.cmo _build/polygon.cmo _build/lightsource.cmo _build/main.cmo

main.cmo: main.re vector.cmo maybe.cmo segment.cmo polygon.cmo lightsource.cmo
		ocamlfind ocamlc -c -package lablgl.glut -pp refmt -I _build -impl main.re
		mv main.cm* _build/

lightsource.cmo: liblightsource.so polygon.cmo vector.cmo lightsource.re
		ocamlfind ocamlc -c -pp refmt -I _build -package ctypes.foreign -impl lightsource.re
		mv lightsource.cm* _build/

polygon.cmo: libpolygon.so vector.cmo polygon.re
		ocamlfind ocamlc -c -pp refmt -I _build -package ctypes.foreign -impl polygon.re
		mv polygon.cm* _build/

segment.cmo: libsegment.so vector.cmo segment.re
		ocamlfind ocamlc -c -pp refmt -I _build -package ctypes.foreign -impl segment.re
		mv segment.cm* _build/

maybe.cmo: libmaybe.so vector.cmo maybe.re
		ocamlfind ocamlc -c -pp refmt -I _build -package ctypes.foreign -impl maybe.re
		mv maybe.cm* _build/

vector.cmo: libvector.so vector.re
		ocamlfind ocamlc -c -pp refmt -I _build -package ctypes.foreign -impl vector.re
		mv vector.cm* _build/

libvector.so: vector.cpp ../primitive/vector.cpp
		clang++ -c -stdlib=libc++ -std=c++11 -fPIC -pedantic -W -Wall -Wextra $(INCLUDES) vector.cpp -o _build/libvector.so

libsegment.so: segment.cpp ../primitive/segment.cpp
		clang++ -c -stdlib=libc++ -std=c++11 -fPIC -pedantic -W -Wall -Wextra $(INCLUDES) segment.cpp -o _build/libsegment.so

libmaybe.so: maybe.cpp
		clang++ -c -stdlib=libc++ -std=c++11 -fPIC -pedantic -W -Wall -Wextra maybe.cpp -o _build/libmaybe.so

libpolygon.so: polygon.cpp ../primitive/polygon.cpp ../primitive/vector.cpp
		clang++ -c -stdlib=libc++ -std=c++11 -fPIC -pedantic -W -Wall -Wextra $(INCLUDES) polygon.cpp -o _build/libpolygon.so

liblightsource.so: lightsource.cpp ../primitive/vector.cpp ../primitive/segment.cpp ../primitive/polygon.cpp ../classes/lightsource.cpp ../classes/component.cpp
		clang++ -c -stdlib=libc++ -std=c++11 -fPIC -pedantic -W -Wall -Wextra -I ./_build lightsource.cpp -o _build/liblightsource.so

_build:
		mkdir -p _build

clean:
		rm -rf _build
