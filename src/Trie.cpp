#include <Trie.hpp>
#include <algorithm>


void FileTrie::push(FileNode entry){
	auto it = std::lower_bound(data.begin(), data.end(), entry);
	data.insert(it, entry);
}


std::string FileTrie::get_match(std::string search){
	int lo = 0;
	int hi	= data.size()-1;
	while (lo <= hi){
		int mid = (hi + lo) / 2;
		switch (starts_with(search, data[mid].fname)){
			case LESSER: 	hi = mid-1; break;
			case GREATER: 	lo = mid+1; break;
			case MATCH: 	return data[mid].rpath;
		}
	}
	throw (std::runtime_error("Does not exist in file trie"));
	return ".";
}


PrefixComp FileTrie::starts_with(const std::string &prefix, const std::string &base){
	int i;
	for (i = 0; i < prefix.size() && i < base.size(); ++i){
		if (prefix[i] < base[i]){
			return LESSER;
		} else if (prefix[i] > base[i]){
			return GREATER;
		}
	}
	return (i == prefix.size()) ? MATCH : GREATER;
}


void FileTrie::print(){
	for (auto &fn : data){
		std::cout << fn.fname << " " << fn.rpath << std::endl;
	}
}




