#pragma once

using json = nlohmann::json;

class I_JSONSerializable
{
public:
	virtual json to_json() const = 0;
	virtual void from_json(const json& json) = 0;
};

class JSONFileIO
{
private:
	using path = std::filesystem::path;
	std::fstream _stream;
	path _path;
public:
	JSONFileIO(path path = path{}) :
		_stream(std::fstream{}), _path(path) { };
	void write_json(I_JSONSerializable& object, const path& file);
	json read_json(const path& file);
};