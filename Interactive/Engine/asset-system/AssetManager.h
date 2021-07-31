#pragma once
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>

struct Scene;
class Entity;
class AssetDatabase;
class Interactive;

class AssetManager
{
private:
	Interactive* Engine;
	bool InitializedDatabase;

public:
	AssetDatabase* Database;

public:
	AssetManager(Interactive* engine);

	void InitializeDatabase();

	Entity* LoadEntityAsset(const char* assetPath);
	Scene* LoadSceneAsset(const char* assetPath);

	template<typename T>
	void InsertToAsset(const char* assetPath, std::string dataId, T dataToInsert)
	{
		using namespace std;

		ofstream file(assetPath, ios::app);

		// Dont judge me. It was 3AM...
		if (&typeid(T) == &typeid(int) || &typeid(T) == &typeid(int long) || &typeid(T) == &typeid(int long long) || &typeid(T) == &typeid(float) || &typeid(T) == &typeid(double) || &typeid(T) == &typeid(double long))
			file << dataId << " = " << dataToInsert << std::endl;
		else if (&typeid(T) == &typeid(string) || &typeid(T) == &typeid(const char*))
			file << dataId << R"( = ")" << dataToInsert << R"(")" << std::endl;
		else if(&typeid(T) == &typeid(std::vector<string>))
		{
			file << dataId << " = {";
			for (int i = 0; i < dataToInsert.size(); ++i)
			{
				file << R"(")" << dataToInsert[i] << R"(")";
				if (i != dataToInsert.size() - 1)
					file << ", ";
			}
			file << "}" << std::endl;
		}
	}

	void DeleteAsset(const char* assetPath)
	{
		std::filesystem::remove(assetPath);
	}
};
