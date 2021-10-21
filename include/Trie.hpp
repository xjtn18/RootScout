#pragma once
#include <jb.hpp>


enum PrefixComp { LESSER, GREATER, MATCH };


struct FileNode {
	std::string fname;
	std::string rpath;
	
	bool operator < (const FileNode &other) const {
		return fname < other.fname;
	}
};


struct FileTrie {
	std::vector<FileNode> data;

	FileTrie() {
		data.reserve(50);
	}

	void push(FileNode entry);
	std::string get_match(std::string search);
	PrefixComp starts_with(const std::string &prefix, const std::string &base);
	void print();
};
