for f in src/*.cpp; do
	bf="$(basename "$f")"
	if [ "$bf" = "main.cpp" ]; then
		continue
	fi
	g++ -c -shared -fPIC "$f" -o "obj/$bf.o" -Wall -Wextra
	echo "obj $f -> obj/$bf.o"
done
ld -shared obj/*.cpp.o -o lib/libzgm.so
echo "ld -> lib/libzgm.so"
ar r lib/libzgm.a obj/*.cpp.o
echo "ar -> lib/libzgm.a"
ranlib lib/libzgm.a
echo "ranlib done"

echo "build complete"
