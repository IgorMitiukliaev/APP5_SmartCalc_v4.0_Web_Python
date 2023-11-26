venv:
	test -d venv || python3.11 -m venv --copies venv && venv/bin/pip install -r requirements.txt

run: venv
	. venv/bin/activate && python3 manage.py runserver 

clean:
	rm -rf venv