#ifndef _FILEPROCESSOR_
#define _FILEPROCESSOR_

#include "Head.h"

class FileReader {
public:
	FileReader(const char *filenamme) {
		this->mFilePtr = fopen(filenamme, "r");
	}

	int GetNextInt() {
		int temp;
		if (fscanf(this->mFilePtr, "%d", &temp) == EOF) {
			return EOF;
		}
		return temp;
	}
	
	int GetNextChar() {
		char temp;
		if (fscanf(this->mFilePtr, "%c", &temp) == EOF) {
			return EOF;
		}
		return temp;
	}

	double GetNextDouble() {
		double temp;
		if (fscanf(this->mFilePtr, "%lf", &temp) == EOF) {
			return EOF;
		}
		return temp;
	}

	void Close() {
		fclose(this->mFilePtr);
	}
	~FileReader() {
		fclose(this->mFilePtr);
	}

private:
	FILE *mFilePtr;
};

class FileWriter {
public:
	FileWriter(const char *filename) {
		this->mFilePtr = fopen(filename, "w");
	}
	FileWriter(const char *filename, char *options) {
		this->mFilePtr = fopen(filename, options);
	}
	void WriteInt(int value) {
		fprintf(this->mFilePtr, "%d ", value);
	}
	void WriteDouble(double value) {
		fprintf(this->mFilePtr, "%lf ", value);
	}
	void Close() {
		fclose(this->mFilePtr);
	}
	~FileWriter() {
		fclose(this->mFilePtr);
	}

private:
	FILE *mFilePtr;
};
#ifdef _LINUX_
class FileDir {
public:
	void GetFiles(const char *dir, vector<string> &files) {
		DIR *dp;
		struct dirent *entry;
		struct stat statbuf;
		if ((dp = opendir(dir)) == NULL) {
			fprintf(stderr, "cannot open directory: %s\n", dir);
			return;
		}
		int tmp = chdir(dir);
		char filename[1024];
		while ((entry = readdir(dp)) != NULL) {
			lstat(entry->d_name, &statbuf);
			if (S_ISDIR(statbuf.st_mode)) {
				if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
					continue;
				GetFiles(entry->d_name, files);
			} else {
				sprintf(filename, "%s/%s", dir, entry->d_name);
				files.push_back(filename);
			}
		}
		tmp = chdir("..");
		closedir(dp);
	}
};
FileDir *gFileDir = new FileDir();
#endif
#endif
