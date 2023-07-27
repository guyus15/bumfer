#ifndef BUMFER_SPOTIFY_WIDGET_H
#define BUMFER_SPOTIFY_WIDGET_H

#include <bumfer/widgets/widget.h>

#include "curl/curl.h"

#include <string>

struct WriteData
{
    char *memory;
    size_t size;
};

class SpotifyWidget : public Widget
{
public:
    SpotifyWidget();

    void Initialise() override;
    void Update() override;
    void Dispose() override;

private:
    CURL *m_curl_handle;
    WriteData *m_write_data;

    std::string m_access_token;
    int m_access_token_expire_time;
    bool m_is_access_token_valid;

    void GetAccessToken();

    friend size_t WriteCallback(void *buffer, size_t size, size_t nmemb, void *userp);
};

size_t WriteCallback(void *buffer, size_t size, size_t nmemb, void *userp);

#endif // BUMFER_SPOTIFY_WIDGET_H