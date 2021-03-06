#include "../include/Frame.h"
#include "../include/MethodArea.h"

int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("Parametros invalidos, o programa deve ser executado com: %s [-e ou -i] caminho_arquivo\n", argv[0]);
		return 1;
	}

	JavaClass leitor(argv[2]);

	if (argv[1][1] == 'e'){
		leitor.run();
	}
	else if (argv[1][1] == 'i'){
		leitor.load();

		if (!leitor.hasMain()){
			printf("O arquivo %s nao possui metodo main\n", argv[2]);
			return -1;
		}
		else if (leitor.getStatus()){
			return leitor.getStatus();
		}

		MethodArea::path = std::string(leitor.getPath());
		MethodArea::addClass(&leitor);

		FrameStack frames(&leitor);
	  	frames.execute();
	}
	else
	{
		printf("Parametros invalidos, o programa deve ser executado com: %s [-e ou -i] caminho_arquivo\n", argv[0]);
		return 1;
	}

	return 0;
}
