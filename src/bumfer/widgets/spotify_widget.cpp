#include <bumfer/widgets/spotify_widget.h>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define SPOTIFY_TOKEN_URL "https://accounts.spotify.com/api/token"
#define SPOTIFY_BASE_URL

SpotifyWidget::SpotifyWidget()
    : m_curl_handle{nullptr},
      m_write_data{nullptr},
      m_is_access_token_valid{false}
{
    m_write_data = (WriteData *)malloc(sizeof(WriteData));
    assert(m_write_data != nullptr);
    m_write_data->memory = (char *)malloc(1);
    m_write_data->size = 0;
}

void SpotifyWidget::Initialise()
{
    m_curl_handle = curl_easy_init();
    assert(m_curl_handle != nullptr);

    GetAccessToken();
}

void SpotifyWidget::Update()
{
    // TODO: Calculate when the access token is expired,
    // setting m_is_access_token_valid to false.

    if (!m_is_access_token_valid)
    {
        // If the access token expires, acquire a new one.
        GetAccessToken();
    }
}

void SpotifyWidget::Dispose()
{
    curl_easy_cleanup(m_curl_handle);
}

void SpotifyWidget::GetAccessToken()
{
    const char *data = "grant_type=client_credentials&client_id=bd4bfee87e1644c0b2959f0509da4308&client_secret=4e3ac42ceb7f48688c614c38c4ea795d";

    curl_easy_setopt(m_curl_handle, CURLOPT_URL, SPOTIFY_TOKEN_URL);
    curl_easy_setopt(m_curl_handle, CURLOPT_HEADER, "Content-Type: application/x-www-form-urlencoded");
    curl_easy_setopt(m_curl_handle, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, m_write_data);
    curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);

    CURLcode res = curl_easy_perform(m_curl_handle);
    assert(res == CURLE_OK);

    size_t header_size;
    res = curl_easy_getinfo(m_curl_handle, CURLINFO_HEADER_SIZE, &header_size);

    rapidjson::Document d;
    d.Parse(m_write_data->memory + header_size);

    assert(d.IsObject());

    rapidjson::Value &access_token_value = d["access_token"];
    m_access_token = access_token_value.GetString();

    rapidjson::Value &access_token_expire_time_value = d["expires_in"];
    m_access_token_expire_time = access_token_expire_time_value.GetInt();

    m_is_access_token_valid = true;

    free(m_write_data->memory);
    m_write_data->memory = (char *)malloc(1);
    m_write_data->size = 0;
}

size_t WriteCallback(void *buffer, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct WriteData *data = (struct WriteData *)userp;

    char *ptr = (char *)realloc(data->memory, data->size + realsize + 1);
    if (!ptr)
    {
        std::cout << "Error: Failed to allocate memory.\n";
        return 0;
    }

    data->memory = ptr;
    memcpy(&(data->memory[data->size]), buffer, realsize);
    data->size += realsize;
    data->memory[data->size] = 0;

    return realsize;
}