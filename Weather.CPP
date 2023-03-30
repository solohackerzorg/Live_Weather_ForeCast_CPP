#include <iostream>
#include <curl/curl.h>

using namespace std;
string A = "\x1b[0;97m";
string B = "\x1b[0;91m";
string C = "\x1b[0;92m";
string D = "\x1b[0;93m";
string E = "\x1b[0;94m";
string F = "\x1b[0;95m";
string G = "\x1b[0;96m";
string H = "\x1b[0m";
string I = "\x1b[0;32m";
string J = "\x1b[0;36m";
string K = "\x1b[0;31m";
string L = "\x1b[0;35m";
string M = "\x1b[0;33m";
string N = "\033[0;37m";
string O = "\x1b[00m";
string P = "\x1b[0;90m";
string Q = "\x1b[00m";
string R = "\x1b[1;30;32m";
string S = "\x1b[0;36m";
string T = "\x1b[0;31m";
string U = "\x1b[0;35m";
string V = "\x1b[0;33m";
string W = "\x1b[0;34m";
string X = "\033[0;37m";
string Y = "\x1b[00m";
string Z = "\x1b[0;90m";
static string response_str;
string sziloveyu = Z + X + C + V + B + N + M + A + S + D + F + G + H + J + K + L;

string linex = "\033[0;97m═══════════════════════════════════════════════";

void sologo() {
    system("clear");
    cout << sziloveyu << "   ▄████████    ▄█    █▄     ▄██████▄  \n";
    cout << "  ███    ███   ███    ███   ███    ███ \n";
    cout << "  ███    █▀    ███    ███   ███    ███\n";
    cout << "  ███         ▄███▄▄▄▄███▄▄ ███    ███ [S]\n";
    cout << "▀███████████ ▀▀███▀▀▀▀███▀  ███    ███ [O]\n";
    cout << "         ███   ███    ███   ███    ███ [L]\n";
    cout << "   ▄█    ███   ███    ███   ███    ███ [O]\n";
    cout << " ▄████████▀    ███    █▀     ▀██████▀  \n";
    cout << linex << endl;
    cout << " Author    : SOLO HACKER\n Version   : 4.3\n Github    : solohackerzorganization \n";
    cout << linex << endl;
    cout << "\tLive Weather Forecast\n" << linex << endl;
}
// callback function to process the response received from the server
static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    response_str.append(ptr, realsize);
    return realsize;
}

// function to fetch weather data using the wttr.in API
bool get_weather_data(string city, string& condition, string& temperature)
{
    CURL *curl;
    CURLcode res;
    string url = "https://wttr.in/" + city + "?format=%C,%t";

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        if(res == CURLE_OK) {
            // parse the response to extract condition and temperature
            size_t comma_pos = response_str.find(",");
            condition = response_str.substr(0, comma_pos);
            size_t space_pos = response_str.find(" ", comma_pos+1);
            temperature = response_str.substr(comma_pos+1, space_pos-comma_pos-1);
            return true;
        }

        curl_easy_cleanup(curl);
    }
    return false;
}

int main() {
    string city;
    sologo();
    cout << "Enter a city name: ";
    getline(cin, city);

    string condition, temperature;
    if (get_weather_data(city, condition, temperature)) {
        cout << "\nThe current temperature in " << city << " is " <<I<< temperature <<N<< " and " <<I<< condition <<N<< " in the city." << endl;
    } else {
        cout << "Unable to fetch weather data." << endl;
    }

    return 0;
}
