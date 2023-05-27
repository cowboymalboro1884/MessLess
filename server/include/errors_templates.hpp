#ifndef ERRORS_TEMPLATES_H
#define ERRORS_TEMPLATES_H
#include "response_template.hpp"

namespace templates::ResponseTemplate {

struct AbstractJSONResponseError : AbstractJSONResponse {
    QString error_text;

    AbstractJSONResponseError(const QString &error_text_)
        : AbstractJSONResponse(response_types[ERROR], "failed", TO_SENDER),
          error_text(error_text_){};

    QJsonDocument to_qjson_document() override {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        main_data["error_text"] = error_text;
        return QJsonDocument(main_data);
    }
};

struct InvalidJSONError : AbstractJSONResponseError {
    static InvalidJSONError &get_instance() {
        static InvalidJSONError instance;
        return instance;
    }

private:
    InvalidJSONError()
        : AbstractJSONResponseError("GOT INVALID QUERY: Invalid JSON"){};
};

struct MissingRequestTypeError : AbstractJSONResponseError {
    static MissingRequestTypeError &get_instance() {
        static MissingRequestTypeError instance;
        return instance;
    }

private:
    MissingRequestTypeError()
        : AbstractJSONResponseError("GOT INVALID QUERY: Missing request type"
          ){};
};

struct ProjectAlreadyExistError : AbstractJSONResponseError {
    static ProjectAlreadyExistError &get_instance() {
        static ProjectAlreadyExistError instance;
        return instance;
    }

private:
    ProjectAlreadyExistError()
        : AbstractJSONResponseError(
              "GOT INVALID QUERY: project with such name already exist"
          ){};
};

struct UnableToCreateTask : AbstractJSONResponseError {
    static UnableToCreateTask &get_instance() {
        static UnableToCreateTask instance;
        return instance;
    }

private:
    UnableToCreateTask()
        : AbstractJSONResponseError("GOT INVALID QUERY: unable to create task"
          ){};
};

struct UnableToChangTaskCondition : AbstractJSONResponseError {
    static UnableToChangTaskCondition &get_instance() {
        static UnableToChangTaskCondition instance;
        return instance;
    }

private:
    UnableToChangTaskCondition()
        : AbstractJSONResponseError(
              "GOT INVALID QUERY: unable to change task condition"
          ){};
};

struct AuthorizationError : AbstractJSONResponseError {
    static AuthorizationError &get_instance() {
        static AuthorizationError instance;
        return instance;
    }

private:
    AuthorizationError()
        : AbstractJSONResponseError(
              "Couldn't authorize: incorrect email or password"
          ){};
};

struct RegistrationUserError : AbstractJSONResponseError {
    static RegistrationUserError &get_instance() {
        static RegistrationUserError instance;
        return instance;
    }

private:
    RegistrationUserError()
        : AbstractJSONResponseError("Couldn't register user"){};
};

struct RegistrationCompanyError : AbstractJSONResponseError {
    static RegistrationCompanyError &get_instance() {
        static RegistrationCompanyError instance;
        return instance;
    }

private:
    RegistrationCompanyError()
        : AbstractJSONResponseError("Couldn't register company"){};
};

}  // namespace templates::ResponseTemplate
#endif  // ERRORS_TEMPLATES_H
