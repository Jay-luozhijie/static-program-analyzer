#include "../../include/model/SynonymLinkageMap.h"

SynonymLinkageMap::SynonymLinkageMap() {}
SynonymLinkageMap::SynonymLinkageMap(std::unordered_map<std::string, std::set<std::string>> linkageMap) {
	this->linkageMap = linkageMap;
}

bool SynonymLinkageMap::isEmpty() {
	return linkageMap.size() == 0;
}

bool SynonymLinkageMap::isEmptyLinkageSet(std::string synonymName) {
	return linkageMap.find(synonymName) == linkageMap.end() || linkageMap.find(synonymName)->second.size() == 0;
}

void SynonymLinkageMap::insertLinkage(std::string linkedSynonymName, std::string linkedSynonymInstance) {
	if (linkageMap.find(linkedSynonymName) == linkageMap.end()) {
		std::set<std::string> linkedSynInstanceSet;
		linkedSynInstanceSet.insert(linkedSynonymInstance);
		linkageMap.insert(std::make_pair<>(linkedSynonymName, linkedSynInstanceSet));
	}
	else {//intersect linked synonym instance list
		linkageMap.find(linkedSynonymName)->second.insert(linkedSynonymInstance);
	}
}

void SynonymLinkageMap::deleteLinkage(std::string linkedSynonymName, std::string linkedSynonymInstance) {
	if (linkageMap.count(linkedSynonymName) != 0) {
		linkageMap.find(linkedSynonymName)->second.erase(linkedSynonymInstance);
		//if (linkageMap.find(linkedSynonymName)->second.size() == 0) {
		//	linkageMap.erase(linkedSynonymName);
		//}
	}
}

std::unordered_map<std::string, std::set<std::string>>& SynonymLinkageMap::getLinkageMap() {
	return this->linkageMap;
}

bool SynonymLinkageMap::containsKey(std::string linkedSynonymName) {
	return linkageMap.find(linkedSynonymName) != linkageMap.end();
}

std::set<std::string>& SynonymLinkageMap::getLinkedSynValueSet(std::string linkedSynName) {
	if (linkageMap.count(linkedSynName) == 0) {
		return std::set<std::string>{};
	}
	else {
		return linkageMap.at(linkedSynName);
	}
}

void SynonymLinkageMap::insertNewEntry(std::string linkedSynName, std::set<std::string> linkageSet) {
	linkageMap.insert(std::make_pair<>(linkedSynName, linkageSet));
}

