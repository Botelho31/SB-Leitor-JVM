#include "../include/JavaClass.h"


JavaClass::JavaClass(char *in){
	if (in) {	
		fileName = in;
	}
	status = -1;
}

JavaClass::JavaClass(std::string in) {

	if (!in.empty()) {
		fileName = new char[in.size() + 1];
		std::copy(in.begin(), in.end(), fileName);
		fileName[in.size()] = 0; 
	}
	status = -1;
}
    
JavaClass::~JavaClass(){
}

int JavaClass::run(){	
	//carrega o bytecode na classe e verifica se nao retornou erro
	if(load() == 0){
		//imprime o bytecode lido
		printClass();
	}

	//retorna o status que indica se houve erro na leitura ou nao
	return this->status;
}

int JavaClass::load(){
	int checkCP;

	if (!fileName){
		printf("%s\n", getError(MISSING_ARGUMENT).c_str());
		return (status = MISSING_ARGUMENT);
	}

	if (!validExtension()) {
		printf("%s\n", getError(INVALID_EXTENSION).c_str());
		return (status = INVALID_EXTENSION);
	}


	classFile = fopen(fileName, "rb");

	if (classFile == NULL){
		printf("%s\n", getError(CANT_OPEN).c_str());
		return (status = CANT_OPEN);
	}

	if (Utils::readU4(classFile) != 0xcafebabe){
		printf("%s\n", getError(INVALID_FILE).c_str());
		return (status = INVALID_FILE);
	}

	minor_version = Utils::readU2(classFile);
	major_version = Utils::readU2(classFile);
    constant_pool = new ConstantPool(classFile);

	access_flags = Utils::readU2(classFile);
	this_class = Utils::readU2(classFile);

	//verifica se o nome do arquivo bate com o nome da class definida no bytecode
	if (!checkThisClass()){
		std::cerr << getError(INVALID_NAME);
		return (status = INVALID_NAME);
	}

	super_class = Utils::readU2(classFile);

	addSuperClass();
	
	interfaces = new Interfaces(classFile);
	fields = new Fields(classFile,constant_pool);
	methods = new Methods(classFile,constant_pool);
	attributes = new Attributes(classFile, constant_pool);

	//verifica se o metodo main esta entre os metodos lidos no bytecode
	foundMain = findMain();

	//verifica se existe o metodo <clinit>
	foundClinit = findClinit();

	//fecha o arquivo
	fclose(classFile);
	classFile = NULL;

	//se nao houve nenhum erro retorna 0
	return (status = 0);
}

void JavaClass::addSuperClass(){
	if(getSuper_class() == 0){
		return;
	}else{
		std::string super_classe_nome = constant_pool->dereferenceIndex(super_class);
		if(super_classe_nome != "java/lang/Object"){
			super_classe_nome = getPath() + super_classe_nome;
			MethodArea::addClass(super_classe_nome);
		}
	}
}

bool JavaClass::findMain()
{
	bool encontrou = false;

	for (int i = 0; i < getMethodsCount(); i++){
		int name = methods->methods[i]->name_index;
		int desc = methods->methods[i]->descriptor_index;
		int flags = methods->methods[i]->access_flags;
		
		//verifica se o nome do metodo se encontra dentro das referencias das constantes
		if ("main" == constant_pool->dereferenceIndex(name)){
			//verifica se o descritor do metodo esta correto
			if ("([Ljava/lang/String;)V" == constant_pool->dereferenceIndex(desc)){
				if ((flags & 0x09) == 0x09){
					mainMethod = i;
					encontrou = true;
					break;
				}
			}
		}
	}

	//se encontrou a main retorna true
	return encontrou;
}


bool JavaClass::findClinit(){
	bool encontrou = false;

	for (int i = 0; i < methods->methods_count; i++){
		//pega o nome do metodo
		int name = methods->methods[i]->name_index;
		
		//verifica se o nome do metodo se encontra nas constantes
		if ("<clinit>" == constant_pool->dereferenceIndex(name)){
			clinit = i;
			encontrou = true;
			break;
		}
	}

	return encontrou;
}

void JavaClass::printClass(){
    //minimo 26 bytes
    // ClassFile {
    //      4-byte         magic;
    //      2-byte         minor_version;
    //      2-byte         major_version;
    //      2-byte         constant_pool_count;
    //      cp_info        constant_pool[constant_pool_count-1];
    //      2-byte         access_flags;
    //      2-byte         this_class;
    //      2-byte         super_class;
    //      2-byte         interfaces_count;
    //      2-byte         interfaces[interfaces_count];
    //      2-byte         fields_count;
    //      field_info     fields[fields_count];
    //      2-byte         methods_count;
    //      method_info    methods[methods_count];
    //      2-byte         attributes_count;
    //      attribute_info attributes[attributes_count];
    //  }

    std::cout << "Minor version -> "<< minor_version << std::endl;
    std::cout << "Major version -> "<< major_version << std::endl;

    std::cout << "-------------------------------------" << std::endl;
    constant_pool->printConstantPool();
    std::cout << "-------------------------------------" << std::endl;
    
    std::cout << "Access flags -> "<< access_flags << std::endl;
    std::cout << "This class -> "<< this_class << std::endl;
    std::cout << "Super class -> "<< super_class << std::endl;

    std::cout << "-------------------------------------" << std::endl;
    interfaces->printInterfaces(constant_pool);
    std::cout << "-------------------------------------" << std::endl;
    fields->printFields(constant_pool);
    std::cout << "-------------------------------------" << std::endl;
    methods->printMethods(constant_pool);
    std::cout << "-------------------------------------" << std::endl;
    attributes->printAttributes(constant_pool);
}

bool JavaClass::validateMagic(u4 magic){
    
    if (magic != 0XCAFEBABE){
        std::cout << "Flag Magic inválida" << std::endl;
        return false;
    }else{

        std::cout << "Flag Magic Validada com sucesso" << std::endl;
        return true;
    }
    
}

bool JavaClass::validExtension (){
	std::string aux = "", auxFilename(this->fileName);
	int size = auxFilename.size();

	if (size > 7){
		for (int i = size-6; i < size; i++){
			aux += auxFilename[i];
		}
	}

	return aux == ".class";
}

bool JavaClass::hasMain (){
	//retorna valor de foundMain
	return foundMain;
}

bool JavaClass::hasClinit (){
	//retorna o valor de foundClinit
	return foundClinit;
}

Method* JavaClass::getMain(){
	if (foundMain){
		return methods->methods[mainMethod];
	} 
	else{
		throw std::runtime_error("Nao foi encontrado um metodo main!\n");
	}
}

Method* JavaClass::getClinit(){
	return methods->methods[clinit];
}

bool JavaClass::checkThisClass (){
	int auxPos;
	
	std::string auxFilename(this->fileName);
	std::string auxClass = constant_pool->dereferenceIndex(this->this_class);
	
	//remove extensao .class
	auxFilename = auxFilename.substr(0, auxFilename.size()-6);
	
	//remove nomes de pastas no Windows
	auxPos = auxFilename.find("\\");

	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()){
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//remove nomes de pastas no Linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()){
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	return (auxClass == auxFilename);
}

int JavaClass::getStatus (){
	return status;
}

std::string JavaClass::getError(int error){
	std::string ret = "";
	switch (error){
		case MISSING_ARGUMENT:
				ret = "ERRO: Argumento passado invalido!\n";
				break;
			case CANT_OPEN:
				ret = "ERRO: nao foi possivel abrir o arquivo \"" + std::string(fileName) + "\"!\n";
				break;
			case INVALID_FILE:
				ret = "ERRO: Arquivo invalido!\nAssinatura \"cafe babe\" nao encontrada.\n";
				break;
			case UNKNOWN_TYPE:
				ret = "ERRO: Tipo nao reconhecido para o pool de constantes!\nNao foi possivel carregar todo o PC.";
				break;
			case INVALID_NAME:
				ret = "ERRO: O nome da classe definida nao bate com o do arquivo!\n";
				break;
			case INVALID_EXTENSION:
				ret = "ERRO: O arquivo deve ter a extensao .class!\n";
				break;
			default:
				break;
	}
	return ret;
}

ConstantPool* JavaClass::getCP() const 
{
	return constant_pool;
}

u2 JavaClass::getLengthCP (){
	return constant_pool->constant_pool_count;
}

char *JavaClass::getPath (){
	std::string path = "", auxFilename(this->fileName);
	char *caminho_arquivo;
	int auxPos;

	//navega pelas pastas do windows
	auxPos = path.find("\\");
	while(auxPos >= 0 && (unsigned int) auxPos <= path.size()){
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//navega pelas pastas do linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()){
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	//copia o resulta para a string caminho_arquivo
	caminho_arquivo = (char *) malloc(sizeof(char) * (path.size() + 1));
	for (unsigned int i = 0; i < path.size(); i++){
		caminho_arquivo[i] = path[i];
	}
	caminho_arquivo[path.size()] = '\0';

	return caminho_arquivo;
}

Methods *JavaClass::getMethods(){
	return methods;
}

u2 JavaClass::getMethodsCount(){
	return methods->methods_count;
}

u2 JavaClass::getThis_class(){
	return this_class;
}

u2 JavaClass::getSuper_class(){
	return super_class;
}

u2 JavaClass::getFieldsCount(){
	return fields->fields_count;
}

Fields *JavaClass::getFields(){
	return fields;
}

Field* JavaClass::getField(std::string field_name){
	//percorre a array com as fields  ate encontrar field desejada
	for(int i = 0; i < getFieldsCount(); i++){
		if(constant_pool->dereferenceIndex(fields->fields[i]->name_index) == field_name ){
			return fields->fields[i]; 
		}
	}
	return NULL;

}

Method* JavaClass::getMethod(std::string name, std::string descriptor)
{
	Method* method;

	for(int i = 0; i < methods->methods_count; i++){
		method = methods->methods[i];
		std::string method_name = constant_pool->dereferenceIndex(method->name_index);
		std::string method_desc = constant_pool->dereferenceIndex(method->descriptor_index);

		if(descriptor == method_desc && name == method_name){
			return method;
		}
	}

	if(getSuper_class() == 0){
		return NULL;
	}
	else{

		ClasseEstatica* a = MethodArea::getClass(constant_pool->dereferenceIndex(getSuper_class()));
		JavaClass* l = a->getDef();

		
		return l->getMethod(name, descriptor);
	}
}

JavaClass* JavaClass::getClassThatHasSearchedMethod(std::string name, std::string descriptor)
{
	Method * method;

	for(int i = 0; i < this->methods->methods_count; i++){
		method = methods->methods[i];

		std::string method_name = this->constant_pool->dereferenceIndex(method->name_index);
		std::string method_desc = this->constant_pool->dereferenceIndex(method->descriptor_index);

		if(descriptor == method_desc && name == method_name){
			return this;
		}
	}

	if(getSuper_class() == 0){
		return NULL;
	}
	else{
		JavaClass* l = MethodArea::getClass(constant_pool->dereferenceIndex(getSuper_class()))->getDef();
		return l->getClassThatHasSearchedMethod(name, descriptor);
	}
}
