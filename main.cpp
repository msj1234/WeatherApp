#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/Http/Client.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <boost/system/error_code.hpp>
#include <Wt/Http/Message.h>

using namespace Wt;

/**
 * @brief Main application class for the weather app.
 *
 * This class represents a web application that allows users to search
 * for weather information and receive packing suggestions based on the
 * temperature.
 */

class WeatherApp : public WApplication {
private:
    double temp_celsius;
    double temp_fahrenheit;

public:
    /**
     * @brief Constructor for WeatherApp.
     *
     * @param env The environment configuration for the application.
     */
    WeatherApp(const Wt::WEnvironment& env);

    Wt::WLineEdit* cityInput_;
    Wt::WPushButton* searchButton_;
    Wt::WPushButton* packButton_;
    Wt::WText* resultTemp_;
    Wt::WText* resultMinMaxTemp_;
    Wt::WText* packingList_;

    /**
     * @brief Initiates a search for weather information based on the entered city.
     */
    void searchWeather();

    /**
     * @brief Handles the HTTP response from the weather API.
     *
     * @param err Error code of the HTTP response.
     * @param response The HTTP response message.
     */
    void handleHttpResponse(boost::system::error_code err, const Wt::Http::Message& response);

    /**
     * @brief Generates a packing list based on the temperature.
     *
     * @param tempCelsius The temperature in Celsius.
     */
    void packingList(double tempCelsius);
};

WeatherApp::WeatherApp(const Wt::WEnvironment& env) : Wt::WApplication(env) {
    enableUpdates(true);

    useStyleSheet("resources/styles.css");
    root()->setStyleClass("container");

    //create and style application heading 
    auto title = root() ->addWidget(std::make_unique<Wt::WText>("Welcome to our Travel Weather App!"));
    title->setStyleClass("app-heading"); 

    //create and style enter city text
    auto cityInputLabel = root()->addWidget(std::make_unique<Wt::WText>("Please Enter Your Destination City:"));
    cityInputLabel->setStyleClass("city-input-label");

    cityInput_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    cityInput_->setId("cityInput");

    searchButton_ = root()->addWidget(std::make_unique<Wt::WPushButton>("Search"));
    searchButton_->setId("searchBtn");
    searchButton_->clicked().connect(this, &WeatherApp::searchWeather);

    resultTemp_ = root()->addWidget(std::make_unique<Wt::WText>());
    resultTemp_->setStyleClass("desc");

    resultMinMaxTemp_ = root()->addWidget(std::make_unique<Wt::WText>());
    resultMinMaxTemp_->setStyleClass("desc");

    packingList_ = root()->addWidget(std::make_unique<Wt::WText>());
    packingList_->setStyleClass("desc");

    // Create the packButton but initially hide it
    packButton_ = root()->addWidget(std::make_unique<Wt::WPushButton>("Get Packing List Ideas"));
    packButton_->setId("packBtn");
    packButton_->hide();
    packButton_->clicked().connect([=] {
        packingList(temp_celsius);
        });
}


void WeatherApp::searchWeather()
{
    std::string city = cityInput_->text().toUTF8();
    std::cout << city << std::endl;
    std::string api = "24610728f106bbc48ea65373766767ac";
    std::string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + api + "&units=metric";
    std::cout << url << std::endl;

    Wt:Http::Client *client = new Wt::Http::Client();
    client->setTimeout(std::chrono::seconds(3));
    client->done().connect(std::bind(&WeatherApp::handleHttpResponse, this, std::placeholders::_1, std::placeholders::_2));

    client->get(url);
}

void WeatherApp::packingList(double tempCelsius) {
   std::stringstream stream;
   stream <<" <li class='packingHeading'>Packing List: </li> " <<std::endl;
   stream <<"<li class='emptyLine'></li>" << std::endl;
   if (tempCelsius <= 0.0) {
       //std::stringstream stream;
       stream << "<li class='accessories'>Accessories: </li>" << std::endl;
       stream << "<li class='listItem'> Scarf </li>" << std::endl;
       stream << "<li class='listItem'> Gloves </li>" << std::endl;
       stream << "<li class='listItem'> Hat </li>" << std::endl;
       stream << "<li class='listItem'> Boots </li>" << std::endl;

       stream << "<li class='accessories'>Clothes:</li>" << std::endl;
       stream << "<li class='listItem'> Sweaters </li>" << std::endl; 
       stream << "<li class='listItem'> Hoodies </li>" << std::endl;
       stream << "<li class='listItem'> Sweatpants </li>" << std::endl;
       stream << "<li class='listItem'> Jeans </li>" << std::endl;
       stream << "<li class='listItem'> Leggings </li>" << std::endl;
       stream << "<li class='listItem'> Jacket </li>" << std::endl;

       stream << "<li class='accessories'> Optional Extras: </li>" << std::endl;
       stream << "<li class='listItem'> Sunglasses </li>" << std::endl;
       stream << "<li class='listItem'> Backpack </li>" << std::endl;
       stream << "<li class='listItem'> Sneakers </li>" << std::endl;

       packingList_->setText(stream.str());
    }
    if (tempCelsius > 0.0 && tempCelsius < 20.0) {

        //std::stringstream stream;
        stream << "<li class='accessories'>Accessories: </li>" << std::endl;
        stream << "<li class='listItem'> Scarf </li>" << std::endl;
        stream << "<li class='listItem'> Purse </li>" << std::endl;
        stream << "<li class='listItem'> Sneakers </li>" << std::endl;

        stream << "<li class='accessories'>Clothes:</li>" << std::endl;
        stream << "<li class='listItem'> Light Jacket </li>" << std::endl; 
        stream << "<li class='listItem'> Rain Jacket </li>" << std::endl;
        stream << "<li class='listItem'> T-Shirt </li>" << std::endl;
        stream << "<li class='listItem'> Long Sleeves </li>" << std::endl;
        stream << "<li class='listItem'> Jeans </li>" << std::endl;
        stream << "<li class='listItem'> Light Pants </li>" << std::endl;
        
        stream << "<li class='accessories'> Optional Extras: </li>" << std::endl;
        stream << "<li class='listItem'> Sunglasses </li>" << std::endl;
        stream << "<li class='listItem'> Backpack </li>" << std::endl;
        stream << "<li class='listItem'> Rainboots </li>" << std::endl;
        
        packingList_->setText(stream.str());
    }
    if (tempCelsius > 20.0) {
        //std::stringstream stream;

        stream << "<li class='accessories'>Accessories: </li>" << std::endl;
        stream << "<li class='listItem'> Sunglasses </li>" << std::endl;
        stream << "<li class='listItem'> Purse </li>" << std::endl;
        stream << "<li class='listItem'> Bathing Suits </li>" << std::endl;

        stream << "<li class='accessories'>Clothes:</li>" << std::endl;
        stream << "<li class='listItem'> Sandals </li>" << std::endl; 
        stream << "<li class='listItem'> Heels </li>" << std::endl;
        stream << "<li class='listItem'> Shorts </li>" << std::endl;
        stream << "<li class='listItem'> T-Shirts </li>" << std::endl;
        stream << "<li class='listItem'> Tank Tops </li>" << std::endl;
        stream << "<li class='listItem'> Skirts </li>" << std::endl;
        
        stream << "<li class='accessories'> Optional Extras: </li>" << std::endl;
        stream << "<li class='listItem'> Beach Bag </li>" << std::endl;
        stream << "<li class='listItem'> Backpack </li>" << std::endl;
        stream << "<li class='listItem'> Hat </li>" << std::endl;
        stream << "<li class='listItem'> Baseball Cap </li>" << std::endl;
        stream << "<li class='listItem'> Jacket </li>" << std::endl;
        packingList_->setText(stream.str());
    }
}

void WeatherApp::handleHttpResponse(boost::system::error_code err, const Wt::Http::Message& response) {
    if (!err) {
        try {
            auto json = nlohmann::json::parse(response.body());
            if (json.contains("main") && json["main"].contains("temp") && json["main"]["temp"].is_number()) {
                temp_celsius = json["main"]["temp"];
                temp_fahrenheit = (temp_celsius * 9.0 / 5.0) + 32;

                std::stringstream stream;
                stream 
                    << "<li class='temp-heading1'>Temperature (Celsius): </li> " << temp_celsius << " °C <br />"
                    << "<li class='temp-heading1'>Temperature (Fahrenheit): </li> " << temp_fahrenheit << " °F";
                resultTemp_->setText(stream.str());

                if (json["main"].contains("temp_min") && json["main"]["temp_min"].is_number() &&
                    json["main"].contains("temp_max") && json["main"]["temp_max"].is_number()) {
                    double min_temp = json["main"]["temp_min"];
                    double max_temp = json["main"]["temp_max"];
                    double min_temp_fahrenheit = (min_temp * 9.0 / 5.0) + 32;
                    double max_temp_fahrenheit = (max_temp * 9.0 / 5.0) + 32;

                    // Set the text with both temperatures
                    std::stringstream stream;
                    stream
                        << "<li class='temp-heading'> Minimum temperature (Celsius): </li> " << min_temp << " °C <br />"
                        << "<li class='temp-heading'> Minimum temperature (Fahrenheit): </li> " << min_temp_fahrenheit << " °F<br />"
                        << "<li class='temp-heading'> Maximum temperature (Celsius): </li> " << max_temp << " °C<br />"
                        << "<li class='temp-heading'> Maximum temperature (Fahrenheit): </li> " << max_temp_fahrenheit << " °F";

                    resultMinMaxTemp_->setText(stream.str());
				}
                else {
                    std::stringstream stream;
                    stream
                        << "Min/Max temperature data is not available.";
                        resultMinMaxTemp_->setText(stream.str());
                }

                // Show the packButton after setting the result text
                packButton_->show();
            }
            else {
                resultTemp_->setText("Temperature data is not available.");
            }
        }
        catch (nlohmann::json::exception& e) {
            resultTemp_->setText(std::string("Error parsing weather data: ") + e.what());
        }
    }
    else {
        resultTemp_->setText("Error fetching weather data");
    }

    // Trigger UI update
    WApplication::instance()->triggerUpdate();
}

/**
 * @brief Entry point for the application.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int The exit code of the application.
 */
int main(int argc, char** argv) {
    return Wt::WRun(argc, argv, [](const WEnvironment& env) {
        return std::make_unique<WeatherApp>(env);
        });
}
