//
//  ViewController.h
//  seniorsender
//
//  Created by Gabe on 10/21/12.
//  Copyright (c) 2012 Corkydev. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <NSStreamDelegate>
{
    
    
    
    __weak IBOutlet UITextField *theipMessageField;
    __weak IBOutlet UITextField *portField;
    __weak IBOutlet UITextField *testMessageField;
    NSInputStream *inputStream;
    NSOutputStream *outputStream;
    NSString *response;
    int pan;
    int tilt;
    int on;
    NSData *data;
}
- (IBAction)hideKeyboard:(id)sender;
- (IBAction)connectButton:(id)sender;
- (IBAction)panValueChanged:(id)sender;
- (IBAction)tiltValueChanged:(id)sender;
- (IBAction)switchValueChanged:(id)sender;
- (IBAction)sendButton:(id)sender;
-(void)initNetworkCommunication;
@end

