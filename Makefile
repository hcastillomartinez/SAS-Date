.PHONY: build
build: 
		echo "Building date parser"
		mkdir -p build &&\
		rm -rf out/* &&\
		./generator.py 1000 &&\
		cd build &&\
		cmake .. &&\
		make

.PHONY: clean
clean:
		rm -rf build/* && rm -rf out/* 

.PHONY: test
test:
		cd out &&\
		./date-parser 200