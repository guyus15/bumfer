#ifndef BUMFER_SPOTIFY_WIDGET_H
#define BUMFER_SPOTIFY_WIDGET_H

#include <bumfer/widgets/widget.h>

#include "curl/curl.h"

struct WriteData
{
    char* memory;
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
    CURL* m_curl_handle;
    WriteData* m_write_data;

    friend size_t WriteCallback(void* buffer, size_t size, size_t nmemb, void* userp);
};

size_t WriteCallback(void* buffer, size_t size, size_t nmemb, void* userp);

#endif // BUMFER_SPOTIFY_WIDGET_H