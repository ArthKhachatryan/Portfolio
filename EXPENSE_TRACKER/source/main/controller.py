'''
This module will contain controllers for Main Menu app.
'''
from .view import MainMenuView
from .model import MainMenuModel
from expenses.controller import ManageExpensesController
from users.controller import LoginController
class MainMenuController:
    '''
    This controller will manage the main menu of the app
    '''


    def start(self):
        '''
        Starting the controllers
        '''

       # Initiate database

        mm_model = MainMenuModel()
        mm_model.init_db()

        # Call Login Controller
        login_controller = LoginController()

        login_controller.start()


        # Display menu options
        mm_view = MainMenuView()
        selected_menu = mm_view.display_menu()


        if selected_menu == 1:
            manage_controller = ManageExpensesController()
            manage_controller.start()
        elif selected_menu == 2:
            manage_controller = ManageExpensesController()
            manage_controller.starter()
        else:
            print("Invalid Menu Option Selected")
            return self.start()
