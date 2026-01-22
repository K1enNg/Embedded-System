#include "domain/task.h"
#include "domain/datetime.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void to_json(json& j, const Task& t) {
    j = json{
        {"id", t.id},
        {"title", t.title},
        {"completed", t.completed},
        {"created_at", DateTime::toISOString(t.created_at)},
        {"due_at", DateTime::toISOString(t.due_at)}
    };
}

void from_json(const json& j, Task& t) {
    j.at("id").get_to(t.id)
    j.at("title").get_to(t.title)
    j.at("completed").get_to(t.completed)

    t.created_at = DateTime::fromISOString(j.at("created_at"));
    t.due_at = DateTime::fromISOString(j.at("due_at"));
}