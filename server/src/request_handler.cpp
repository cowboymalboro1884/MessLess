#include <map>
#include "query_types.hpp"

using namespace templates::ResponseTemplate;

RequestHandler::RequestHandler(messless::Database *database_)
    : database(database_) {
}

QJsonDocument RequestHandler::proccess_data(const QByteArray &incoming_data
) const {
    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(incoming_data, &json_data_error);

    if (json_data_error.errorString().toInt() == QJsonParseError::NoError) {
        QString event_type = json_data.object().value("type").toString();

        if (!event_type.size()) {
            return MissingRequestTypeError::get_instance().to_qjson_document();
        }

        if (request_types.find(event_type) == request_types.end()) {
            qDebug() << "RH: Got wrong request";
            return InvalidJSONError::get_instance().to_qjson_document();
        }

        REQUEST_TYPE request_type = request_types[event_type];

        qDebug() << event_type;

        return (this->*requests_handlers[request_type])(json_data.object());
    } else {
        qDebug() << "RH: Got wrong request";
        return InvalidJSONError::get_instance().to_qjson_document();
    }
}
