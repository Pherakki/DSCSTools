﻿// DSCSTools.cpp : Defines the entry point for the application.
//

#include "DSCSTools.h"
#include "MDB1.h"
#include "SaveFile.h"
#include "EXPA.h"

void printUse() {
	std::cout << "Modes:" << std::endl;
	std::cout << "	--extract <sourceFile> <targetFolder>" << std::endl;
	std::cout << "		Extracts the given decrypted MDB1 into a folder." << std::endl;
	std::cout << "	--pack <sourceFolder> <targetFile> [--disable-compression]" << std::endl;
	std::cout << "		Repacks the given folder into a decrypted MDB1." << std::endl;
	std::cout << "		Optional --disable-compression. Don't use for archives >= 4GiB!" << std::endl;
	std::cout << "	--crypt <sourceFile> <targetFolder>" << std::endl;
	std::cout << "		De- and Encrypts a mvgl file using the keys from DSCS." << std::endl;
	std::cout << "	--savedecrypt <sourceFile> <targetFolder>" << std::endl;
	std::cout << "		Decrypts a savefile (system_data.bin, 000X.bin, slot_000X.bin)." << std::endl;
	std::cout << "	--saveencrypt <sourceFile> <targetFolder>" << std::endl;
	std::cout << "		Encrypts a savefile (system_data.bin, 000X.bin, slot_000X.bin)." << std::endl;
	std::cout << "	--mbeextract <source> <targetFolder>" << std::endl;
	std::cout << "		Extracts a .mbe file or a directory of them into CSV, " << std::endl;
	std::cout << "		as long as it's structure is defined in the structure.json file." << std::endl;
	std::cout << "	--mbepack <sourceFolder> <targetFile>" << std::endl;
	std::cout << "		Repacks an .mbe folder containing CSV files back into a .mbe file " << std::endl;
	std::cout << "		as long as it's structure is found and defined in the structure.json file." << std::endl;
}

int main(int argc, char** argv) {
	if (argc < 4) {
		printUse();
		return 0;
	}

	boost::filesystem::path source = boost::filesystem::exists(argv[2]) ? argv[2] : boost::filesystem::current_path().append(argv[2]);
	boost::filesystem::path target = boost::filesystem::exists(argv[3]) ? argv[3] : boost::filesystem::current_path().append(argv[3]);
	
	if (strncmp("--extract", argv[1], 10) == 0) {
		extractMDB1(source, target);
		std::cout << "Done" << std::endl;
	}
	else if (strncmp("--pack", argv[1], 7) == 0) {
		bool compress = argc < 5 || (argv[4] == "--disable-compression");
		packMDB1(source, target, compress);
		std::cout << "Done" << std::endl;
	}
	else if (strncmp("--crypt", argv[1], 8) == 0) {
		cryptFile(source, target);
		std::cout << "Done" << std::endl;
	}
	else if (strncmp("--savedecrypt", argv[1], 14) == 0) {
		decryptSaveFile(source, target);
		std::cout << "Done" << std::endl;
	}
	else if (strncmp("--saveencrypt", argv[1], 14) == 0) {
		encryptSaveFile(source, target);
		std::cout << "Done" << std::endl;
	}
	else if (strncmp("--mbeextract", argv[1], 13) == 0) {
		extractMBE(source, target);
		std::cout << "Done" << std::endl;
	}
	else if (strncmp("--mbepack", argv[1], 10) == 0) {
		packMBE(source, target);
		std::cout << "Done" << std::endl;
	}
	else {
		printUse();
	}

	return 0;
}

