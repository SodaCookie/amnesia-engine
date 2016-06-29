app.out: main.cmo vector.cmo maybe.cmo segment.cmo libvector.so libmaybe.so libsegment.so
	  ocamlfind ocamlc -o app.out -I _build -linkpkg -custom -package ctypes.foreign \
	    -cclib -L. -cclib -lvector -cclib -lsegment -cclib -lmaybe \
			_build/vector.cmo _build/maybe.cmo _build/segment.cmo _build/main.cmo

main.cmo: main.re vector.cmo maybe.cmo segment.cmo
		ocamlfind ocamlc -c -pp refmt -I _build -impl main.re
		mv main.cm* _build/

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
		g++ --std=c++11 -shared -fPIC -ansi -pedantic -W -Wall vector.cpp -o libvector.so

libsegment.so: _build segment.cpp ../primitive/segment.cpp
		g++ --std=c++11 -shared -fPIC -ansi -pedantic -W -Wall segment.cpp -o libsegment.so

libmaybe.so: _build maybe.cpp
		g++ --std=c++11 -shared -fPIC -ansi -pedantic -W -Wall maybe.cpp -o libmaybe.so

_build:
		mkdir -p _build

clean:
		rm -rf _build libvector.so libmaybe.so libsegment.so app.out
