<?php
/**
 * @file
 * AWS SQS module admin functions.
 */

/**
 * Menu callback for admin form.
 */
function aws_sqs_settings_form() {
  $form['credentials'] = array(
    '#type' => 'fieldset',
    '#title' => t('AWS credentials'),
    '#description' => t('Follow the instructions to set up your AWS credentials !here.',
      array('!here' => l('here', 'http://docs.aws.amazon.com/AWSSimpleQueueService/latest/SQSGettingStartedGuide/AWSCredentials.html'))),
  );
  $form['credentials']['aws_sqs_aws_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Access Key ID'),
    '#default_value' => variable_get('aws_sqs_aws_key', ''),
    '#required' => TRUE,
    '#description' => t('Amazon Web Services Key.'),
  );
  $form['credentials']['aws_sqs_aws_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret Access Key'),
    '#default_value' => variable_get('aws_sqs_aws_secret', ''),
    '#required' => TRUE,
    '#description' => t('Amazon Web Services Secret Key.'),
  );

  $seconds = range(0, 20);
  $form['aws_sqs_waittimeseconds'] = array(
    '#type' => 'select',
    '#title' => t('How long can the fetchItem call wait before it times out? (seconds)'),
    '#default_value' => variable_get('aws_sqs_waittimeseconds', ''),
    '#options' => $seconds,
    '#description' => t('This is important if you want to reduce the amount of polls to the AWS service. It is comparable with a blocking select call.'),
  );

  $form['aws_sqs_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send all Queues to the amazon queue system'),
    '#default_value' => variable_get('aws_sqs_enable', ''),
    '#description' => t('Switches the default queue class to the aws queue class.'),
  );
  $form['#submit'][] = 'aws_sqs_settings_form_submit';
  return system_settings_form($form);
}

/**
 * Submit callback for admin settings form.
 */
function aws_sqs_settings_form_submit($form, &$form_state) {
  if (!empty($form_state['values']['aws_sqs_enable'])) {
    variable_set('queue_default_class', 'awsSqsQueue');
  }
}
