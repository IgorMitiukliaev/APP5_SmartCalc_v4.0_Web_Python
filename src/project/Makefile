venv:
	test -d env || python3 -m venv --copies env && env/bin/pip install -r requirements.txt

run: venv lib migrate
	. env/bin/activate && python3 manage.py runserver 

lib:
	test -f ./cpp/calc.so || g++ -Wall -lstdc++ -shared -o ./cpp/calc.so -fPIC ./cpp/wrapper.cpp ./cpp/Model.cpp

migrate:
	python3 manage.py makemigrations basecalc
	python3 manage.py migrate basecalc

clean:
	rm -f cpp/*.so
	rm -rf env