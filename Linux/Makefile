TARGET += ./bin/banksort \
		  ./bin/circular_buffer
		  
all:$(TARGET)
./bin/%: ./%.cc
	g++ -o $(@) $(<) -g
	
.PHONY:clean
clean:
	rm -rf ./bin/*
