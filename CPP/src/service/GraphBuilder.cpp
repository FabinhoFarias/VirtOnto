#include "service/GraphBuilder.hpp"
#include "model/Node.hpp"
#include "model/Edge.hpp"
#include <regex>

namespace virtonto::service {

model::Graph GraphBuilder::buildFromJSON(const std::string& rawJson) {
    model::Graph graph;

    auto parseNodesSection = [&]() {
        size_t nodesPos = rawJson.find("\"nodes\"");
        if (nodesPos == std::string::npos) return;
        size_t arrayStart = rawJson.find('[', nodesPos);
        size_t arrayEnd = rawJson.find(']', arrayStart);
        if (arrayStart == std::string::npos || arrayEnd == std::string::npos) return;
        std::string nodesStr = rawJson.substr(arrayStart, arrayEnd - arrayStart);

        std::regex idR(R"(\"id\"\s*:\s*\"([^\"]+)\")");
        std::regex labelR(R"(\"label\"\s*:\s*\"([^\"]*)\")");
        std::regex typeR(R"(\"type\"\s*:\s*(\d+))");
        std::regex xR(R"(\"x\"\s*:\s*([\-0-9\.eE]+))");
        std::regex yR(R"(\"y\"\s*:\s*([\-0-9\.eE]+))");
        std::regex zR(R"(\"z\"\s*:\s*([\-0-9\.eE]+))");

        std::regex objR(R"(\{([^}]+)\})");
        auto begin = std::sregex_iterator(nodesStr.begin(), nodesStr.end(), objR);
        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            std::string obj = it->str();
            std::smatch m;
            std::string id = std::regex_search(obj, m, idR) ? m[1].str() : "";
            if (id.empty()) continue;
            std::string label = std::regex_search(obj, m, labelR) ? m[1].str() : id;
            int typeInt = std::regex_search(obj, m, typeR) ? std::stoi(m[1].str()) : 0;
            float x = std::regex_search(obj, m, xR) ? std::stof(m[1].str()) : 0.0f;
            float y = std::regex_search(obj, m, yR) ? std::stof(m[1].str()) : 0.0f;
            float z = std::regex_search(obj, m, zR) ? std::stof(m[1].str()) : 0.0f;

            // Ordem corrigida: (id, label, type)
            auto node = std::make_shared<model::Node>(id, label, static_cast<model::NodeType>(typeInt));
            node->setPosition({x, y, z});
            graph.addNode(node);
        }
    };

    auto parseEdgesSection = [&]() {
        size_t edgesPos = rawJson.find("\"edges\"");
        if (edgesPos == std::string::npos) return;
        size_t arrayStart = rawJson.find('[', edgesPos);
        size_t arrayEnd = rawJson.find(']', arrayStart);
        if (arrayStart == std::string::npos || arrayEnd == std::string::npos) return;
        std::string edgesStr = rawJson.substr(arrayStart, arrayEnd - arrayStart);

        std::regex idR(R"(\"id\"\s*:\s*\"([^\"]+)\")");
        std::regex srcR(R"(\"source\"\s*:\s*\"([^\"]+)\")");
        std::regex tgtR(R"(\"target\"\s*:\s*\"([^\"]+)\")");
        std::regex labelR(R"(\"label\"\s*:\s*\"([^\"]*)\")");

        std::regex objR(R"(\{([^}]+)\})");
        auto begin = std::sregex_iterator(edgesStr.begin(), edgesStr.end(), objR);
        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            std::string obj = it->str();
            std::smatch m;
            std::string id = std::regex_search(obj, m, idR) ? m[1].str() : "";
            std::string src = std::regex_search(obj, m, srcR) ? m[1].str() : "";
            std::string tgt = std::regex_search(obj, m, tgtR) ? m[1].str() : "";
            std::string label = std::regex_search(obj, m, labelR) ? m[1].str() : "";
            if (id.empty() || src.empty() || tgt.empty()) continue;

            // Ordem corrigida: (id, label, source, target)
            auto edge = std::make_shared<model::Edge>(id, label, src, tgt);
            graph.addEdge(edge);
        }
    };

    parseNodesSection();
    parseEdgesSection();

    return graph;
}

} // namespace virtonto::service