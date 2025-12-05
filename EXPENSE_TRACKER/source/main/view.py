'''
This module will contain all MainMenu views
'''


class MainMenuView:
    ''' This view will handle main menu user interface
    '''

    def display_menu(self)->int:
        """Display the main menu 

        Returns:
            int: return selected option
        """
        print("### Main Menu view ###")
        print("1. Manage Expenses (add, view)")
        print("2. See reports")
        selected_option = int(input("Enter the main menu option (i.e. 1 or 2)"))
        return selected_option


    
