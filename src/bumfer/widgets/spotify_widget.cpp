#include <bumfer/widgets/spotify_widget.h>

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define SPOTIFY_TOKEN_URL "https://accounts.spotify.com/api/token"
#define SPOTIFY_BASE_URL 

SpotifyWidget::SpotifyWidget()
    : m_curl_handle{ nullptr }, m_write_data{ nullptr }
{
    m_write_data = (WriteData*)malloc(sizeof(WriteData));
    assert(m_write_data != nullptr);
    m_write_data->memory = (char*)malloc(1);
    m_write_data->size = 0;
}

void SpotifyWidget::Initialise()
{
    m_curl_handle = curl_easy_init();
    assert(m_curl_handle != nullptr);
}

void SpotifyWidget::Update()
{
    static int count = 0;

    const char* data = "grant_type=client_credentials&client_id=bd4bfee87e1644c0b2959f0509da4308&client_secret=4e3ac42ceb7f48688c614c38c4ea795d";

    curl_easy_setopt(m_curl_handle, CURLOPT_URL, SPOTIFY_TOKEN_URL);
    curl_easy_setopt(m_curl_handle, CURLOPT_HEADER, "Content-Type: application/x-www-form-urlencoded");
    curl_easy_setopt(m_curl_handle, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, m_write_data);
    curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);

    CURLcode res = curl_easy_perform(m_curl_handle);
    assert(res == CURLE_OK);

    std::cout << "------------------------> Bytes received: " << m_write_data->size << "\n";
    std::cout << "------------------------> Data: " << m_write_data->memory << "\n";

    free(m_write_data->memory);
    m_write_data->memory = (char*)malloc(1);
    m_write_data->size = 0;
}

void SpotifyWidget::Dispose()
{
    curl_easy_cleanup(m_curl_handle);
}

size_t WriteCallback(void *buffer, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct WriteData *data = (struct WriteData *)userp;

    char *ptr = (char*)realloc(data->memory, data->size + realsize + 1);
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