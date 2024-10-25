"""This module will contain all controller for users app
"""

from .model import UsersModel
from .view import RegisterView,LoginView

class LoginController:
    """Start the controller
    """

    def start(self)->None:
        """Start the controller
        """
        user_model = UsersModel()
        if user_model.admin_exists():
           login_view = LoginView()
           credentials = login_view.get_credentials()
           validate = user_model.validate_admin(credentials["username"], credentials["password"])
           if not validate:
            print("Invalid credentials. Try again \n")
            return self.start()
        else:
            register_view = RegisterView()
            user_info = register_view.get_user_info()
            
            user_model.create_admin(user_info["username"],user_info["password"])
            return self.start()
        

