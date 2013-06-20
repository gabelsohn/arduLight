//
//  ViewController.m
//  seniorsender
//
//  Created by Gabe on 10/21/12.
//  Copyright (c) 2012 Corkydev. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    pan = 0;
    tilt = 90;
    on = 0;
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    // Dispose of any resources that can be recreated.
}

- (IBAction)connectButton:(id)sender {
    [self initNetworkCommunication];
}

- (IBAction)panValueChanged:(UISlider *)sender{
    pan = sender.value;
    response = [NSString stringWithFormat:@"%i!%i!%i!", pan,tilt,on];
    data = [response dataUsingEncoding:NSASCIIStringEncoding];
    [self initNetworkCommunication];
    [outputStream write:[data bytes] maxLength:[data length]];
    [self stopNetworkCommunication];
}

- (IBAction)tiltValueChanged:(UISlider *)sender{
    tilt = sender.value;
    response = [NSString stringWithFormat:@"%i!%i!%i!", pan,tilt,on];
    data = [response dataUsingEncoding:NSASCIIStringEncoding];
    [self initNetworkCommunication];
    [outputStream write:[data bytes] maxLength: [data length]];
    [self stopNetworkCommunication];
}

- (IBAction)sendButton:(id)sender {
    response  = [NSString stringWithFormat:@"%@", testMessageField.text];
	data = [response dataUsingEncoding:NSASCIIStringEncoding];
    [self initNetworkCommunication];
	[outputStream write:[data bytes] maxLength:[data length]];
    [self stopNetworkCommunication];
}

- (IBAction)hideKeyboard:(id)sender{
    [self.view endEditing:YES];
}

- (IBAction)switchValueChanged:(UISwitch *)sender{
    if (sender.on) {
        on=1;
    }
    else on=0;
    response = [NSString stringWithFormat:@"%i!%i!%i!", pan,tilt,on];
    data= [response dataUsingEncoding:NSASCIIStringEncoding];
    [self initNetworkCommunication];
    [outputStream write:[data bytes] maxLength:[data length]];
    [self stopNetworkCommunication];
    
}

- (void)initNetworkCommunication {
    int portNum = [portField.text integerValue];
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    CFStreamCreatePairWithSocketToHost(NULL, (__bridge CFStringRef) theipMessageField.text, portNum, &readStream, &writeStream);
    inputStream = (__bridge NSInputStream *)readStream;
    outputStream = (__bridge NSOutputStream *)writeStream;
    [inputStream setDelegate:self];
    [outputStream setDelegate:self];
    [inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [inputStream open];
    [outputStream open];
    
    
}

-(void)stopNetworkCommunication{
    [inputStream close];
    [outputStream close];
    
    
    
}
@end

