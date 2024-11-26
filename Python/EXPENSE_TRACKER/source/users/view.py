"""This mudule will contain all user authentication related functionalities
"""
from typing import Dict
from getpass import getpass
class RegisterView:
    """This view will handle Admin registration
    """

    def get_user_info(self)->Dict:
        """Gather admin user info

        Returns:
            Dict: username, password in dict
        """
        print("### Create Admin Account ###")
        credentials = {}
        credentials["username"] = input("Username: ")
        credentials["password"] = getpass("Password: ")
        repeat_password = getpass("Repeat Password: ")

        if repeat_password != credentials["password"]:
            print("Password doesn't match. Try again! \n")
            return self.get_user_info()


        return credentials


class LoginView:
    """This view will handle admin login
    """
    def get_credentials(self)->Dict:
        """Gather user login credentials

        Returns:
            Dict: return credentials in dict (username, password)
        """
        credentials = { }

        print("### Enter Admin credentials to login ###")
        credentials["username"] = input("Username: ")
        credentials["password"] = getpass("Password: ")
           
        return credentials