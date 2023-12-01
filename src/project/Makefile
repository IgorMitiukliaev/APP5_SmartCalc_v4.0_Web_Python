venv:
	test -d env || python3 -m venv --copies env && env/bin/pip install -r requirements.txt

run: venv lib
	. env/bin/activate && python3 manage.py runserver 

lib:
	g++ -Wall -lstdc++ -shared -o ./cpp/calc.so -fPIC ./cpp/wrapper.cpp ./cpp/Model.cpp

clean:
	rm -f cpp/*.so
	rm -rf env