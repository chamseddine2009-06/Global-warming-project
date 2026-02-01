main:
	@clear
	@echo "deleting main if exicet ..."
	@if [ -f "main" ]; then \
		rm main; \
	fi;
	
	@echo "Compailing ..."
	@g++  main.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	@if [ -f "main" ];then \
		echo "************************* Runing *************************";\
		./main; \
	fi;

	@echo "deleting main if exicet ..."
	@if [ -f "main" ]; then \
	rm main; \
	fi;

