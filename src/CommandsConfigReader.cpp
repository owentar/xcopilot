#include "CommandsConfigReader.h"

#include <algorithm>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#include "Command.h"

using namespace xcopilot;
namespace pt = boost::property_tree;

static std::map<std::string, CommandType> commandTypeProvider = {
    { "int", CommandType::INT },
    { "float", CommandType::FLOAT },
    { "double", CommandType::DOUBLE }
};

std::vector<std::string> readDataRefs(const pt::ptree& node) {
    std::vector<std::string> dataRefs;
    std::transform(std::begin(node), std::end(node), std::back_inserter(dataRefs),
                   [](const pt::ptree::value_type& value) { return value.second.get<std::string>(""); });
    return dataRefs;
}

std::vector<Command> CommandsConfigReader::getCommandsForAircraft() {
    pt::ptree root;
    pt::read_json("config/default-commands.json", root);
    std::vector<Command> commands;

    for (auto& node : root) {
        auto name = node.first;
        auto type = node.second.get<std::string>("type");
        auto regex = node.second.get<std::string>("regex");
        auto dataRefs = readDataRefs(node.second.get_child("dataRefs"));
        commands.push_back(Command{name, commandTypeProvider[type], regex, dataRefs, xPlaneSDK});
        std::cout << "Command: " << name << " - Regex: " << regex << std::endl;
    }

    return commands;
}
