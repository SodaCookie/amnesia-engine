app.out: main.cmo vector.cmo maybe.cmo segment.cmo polygon.cmo libvector.so libpolygon.so liblightsource.so libmaybe.so libsegment.so
	  ocamlfind ocamlc -o _build/app.out -I _build -linkpkg -custom -package ctypes.foreign \
	    -cclib -L. -cclib -lvector -cclib -lsegment -cclib -lmaybe -cclib -lpolygon -cclib -llightsource \
			_build/vector.cmo _build/maybe.cmo _build/segment.cmo _build/polygon.cmo _build/lightsource.cmo _build/main.cmo

main.cmo: main.re vector.cmo maybe.cmo segment.cmo polygon.cmo lightsource.cmo
		ocamlfind ocamlc -c -pp refmt -I _build -impl main.re
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

libvector.so: _build vector.cpp ../primitive/vector.cpp
		clang++ -stdlib=libc++ -std=c++11 -shared -fPIC -pedantic -W -Wall vector.cpp -o libvector.so

libsegment.so: _build segment.cpp ../primitive/segment.cpp
		clang++ -stdlib=libc++ -std=c++11 -shared -fPIC -pedantic -W -Wall segment.cpp -o libsegment.so

libmaybe.so: _build maybe.cpp
		clang++ -stdlib=libc++ -std=c++11 -shared -fPIC -pedantic -W -Wall maybe.cpp -o libmaybe.so

libpolygon.so: _build polygon.cpp ../primitive/polygon.cpp
		clang++ -stdlib=libc++ -std=c++11 -shared -fPIC -pedantic -W -Wall -L ./_build -I ./_build polygon.cpp -o libpolygon.so

liblightsource.so: _build lightsource.cpp ../primitive/vector.cpp ../primitive/segment.cpp ../primitive/polygon.cpp ../classes/lightsource.cpp ../classes/component.cpp
		clang++ -stdlib=libc++ -std=c++11 -shared -fPIC -pedantic -W -Wall -L ./_build -I ./_build lightsource.cpp ../primitive/vector.cpp ../primitive/segment.cpp ../primitive/polygon.cpp ../classes/component.cpp ../classes/lightsource.cpp -o liblightsource.so

_build:
		mkdir -p _build

clean:
		rm -rf _build libvector.so libmaybe.so libsegment.so libpolygon.so liblightsource.so
