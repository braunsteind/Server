
#ifndef EX2_CONFIGURATIONFILEHANDLER_H
#define EX2_CONFIGURATIONFILEHANDLER_H


class ConfigurationFileHandler {
public:
    /**
     * This function reads the information from
     * the configuration file
     */
    void readConfigurationFile();
    /**
     * This function returns the server's Port
     *
     * @return the Port number
     */
    int getPortFromFile();

private:
    int port;
};


#endif //EX2_CONFIGURATIONFILEHANDLER_H
