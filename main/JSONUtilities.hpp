#pragma once

using json = nlohmann::json;

class I_JSONSerializable
{
public:
	virtual json& to_json() = 0;
	virtual void from_json(json& json) = 0;
};

class JSONWriter
{
private:
	using path = std::filesystem::path;
	std::fstream _stream;
	path _path;
public:
	JSONWriter(path path = path{}) :
		_stream(std::fstream{}), _path(path) { };
	void write_json(I_JSONSerializable& object, const path& file);
	const json& read_json(const path& file);
};