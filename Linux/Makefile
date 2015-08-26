TARGET += ./bin/banksort \
		  ./bin/circular_buffer \
		  ./bin/curl_test
		  
all:$(TARGET)
./bin/%: ./%.cc
	g++ -o $(@) $(<) -g
	
./bin/curl_test: ./curl_test.cc	
	g++ -o ./bin/curl_test curl_test.cc -lcurl -g
	
.PHONY:clean
clean:
	rm -rf ./bin/*
